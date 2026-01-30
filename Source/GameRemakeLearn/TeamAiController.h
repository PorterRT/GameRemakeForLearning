// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "AIController.h"
#include "DetourCrowdAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "NavigationSystem.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "GenericTeamAgentInterface.h"
#include "TeamAiController.generated.h"


/**
 * 
 */


UCLASS()
class GAMEREMAKELEARN_API ATeamAiController : public ADetourCrowdAIController
{
	GENERATED_BODY()

public:


	UFUNCTION(BlueprintCallable, Category = "Team")
	ETeamAttitude::Type GetTeamAttitudeTowardsActor(const AActor* OtherActor) const;

	
	

protected:

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	// Your actual target variable
	UPROPERTY(BlueprintReadOnly, Category = "AI")
	AActor* AcquiredTarget;

	// Cached reference to controlled character
	UPROPERTY(BlueprintReadOnly, Category = "AI")
	class ACharacter* ControlledCharacter;
	
};
