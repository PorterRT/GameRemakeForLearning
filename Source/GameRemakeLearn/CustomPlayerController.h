// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEREMAKELEARN_API ACustomPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    // IGenericTeamAgentInterface implementation
    UFUNCTION(BlueprintCallable, Category = "Team")
    virtual FGenericTeamId GetGenericTeamId() const override;

private:
    FGenericTeamId TeamId;
};
	

