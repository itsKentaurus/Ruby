// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "CycleSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, DefaultConfig, meta = (DisplayName = "Cycle Settings"))
class CYCLE_API UCycleSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	// This is the length of time for a segment in seconds
	UPROPERTY(EditAnywhere, config)
	float SegmentLength = 15 * 60;

	UPROPERTY(EditAnywhere, config)
	TArray<FGameplayTag> CycleSequence;
};
