// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"

void ACustomPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Set player to Team ID 0 (AI enemies are Team ID 2)
    TeamId = FGenericTeamId(0);

    // Optional: Print for debugging
    UE_LOG(LogTemp, Warning, TEXT("Player Controller Team ID set to: %d"), TeamId.GetId());
}

FGenericTeamId ACustomPlayerController::GetGenericTeamId() const
{
    return TeamId;
}

