// Fill out your copyright notice in the Description page of Project Settings.

#include "TeamAiController.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"




ETeamAttitude::Type ATeamAiController::GetTeamAttitudeTowardsActor(const AActor* OtherActor) const
{
	if (!OtherActor)
	{
		return ETeamAttitude::Neutral;
	}

	return GetTeamAttitudeTowards(*OtherActor);
}




void ATeamAiController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (!Actor) return;

    ETeamAttitude::Type Attitude = FGenericTeamId::GetAttitude(this, Actor);

    // If it's a teammate, we return IMMEDIATELY. 
    // This prevents the AI from updating its "Last Sensed Stimulus" variables.
    if (Attitude == ETeamAttitude::Friendly)
    {
        return;
    }

	// Handle hostile targets
	if (Stimulus.WasSuccessfullySensed())
	{
		AcquiredTarget = Actor;
		UE_LOG(LogTemp, Warning, TEXT("%s acquired target: %s"), *GetName(), *Actor->GetName());
	}
	else
	{
		// Target lost - clear if this was our current target
		if (AcquiredTarget == Actor)
		{
			AcquiredTarget = nullptr;
			
			UE_LOG(LogTemp, Warning, TEXT("%s lost target: %s"), *GetName(), *Actor->GetName());
		}
	}
}

void ATeamAiController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Cache the character reference
	ControlledCharacter = Cast<ACharacter>(InPawn);

	if (ControlledCharacter)
	{
		// Set up character capsule for proper collision/spacing
		UCapsuleComponent* Capsule = ControlledCharacter->GetCapsuleComponent();
		if (Capsule)
		{
			// Adjust radius based on your character model size
			Capsule->SetCapsuleRadius(50.0f);
			Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		}

		UE_LOG(LogTemp, Warning, TEXT("%s possessed %s"), *GetName(), *ControlledCharacter->GetName());
	}

	// Set up crowd avoidance (DetourCrowdAIController already has CrowdFollowingComponent)
	UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());
	if (CrowdComp)
	{
		// High quality avoidance for smooth separation
		CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);

		// Increase separation weight to keep them further apart
		CrowdComp->SetCrowdSeparationWeight(2.5f); // Try 1.5-3.0, higher = more space

		// How far they look for other AI to avoid
		CrowdComp->SetCrowdCollisionQueryRange(600.0f); // Try 400-800

		// Set avoidance groups (teammates avoid each other)
		CrowdComp->SetAvoidanceGroup(1);     // This AI is in group 1
		CrowdComp->SetGroupsToAvoid(1);      // Avoid others in group 1
		CrowdComp->SetGroupsToIgnore(0);     // Don't ignore any groups

		// Optional: Adjust avoidance range multiplier
		CrowdComp->SetCrowdAvoidanceRangeMultiplier(1.0f); // Default 1.0

		UE_LOG(LogTemp, Warning, TEXT("Crowd avoidance configured for %s"), *GetName());
	}
}

