// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameplayTagContainer.h"

#include "CycleDataTypes.generated.h"

UENUM(BlueprintType)
enum class ECycleSegmentType : uint8
{
	Day,
	Night
};

USTRUCT(BlueprintType)
struct FCycleDefinition
{
	GENERATED_BODY()

	int32 CycleIndex = -1;
	float StartTime = -1.f;
	float CurrentTime = 0.f;
	float Multiplier = 1.f;
	bool bIsRunning = false;
	bool bIsComplete = false;

	FString ToString() const
	{
		return FString::Printf(TEXT("CycleDefinition: %d, %f, %f, %f, %d, %d"), CycleIndex, StartTime, CurrentTime, Multiplier, bIsRunning, bIsComplete);
	}
};