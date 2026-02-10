// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "MasterCharacterBase.generated.h"

UCLASS()
class GAMEREMAKELEARN_API AMasterCharacterBase : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMasterCharacterBase();

	virtual void PossessedBy(AController* NewController) override;

	// Team ID handling
	UFUNCTION(BlueprintCallable, Category = "Team")
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamId) override { TeamId = NewTeamId; }
	UFUNCTION(BlueprintCallable, Category = "Team")
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
	FGenericTeamId TeamId = FGenericTeamId::NoTeam;

	UFUNCTION(BlueprintCallable, Category = "Team")
	int32 GetTeamIdAsInt() const { return (int32)TeamId.GetId(); }

private:


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
