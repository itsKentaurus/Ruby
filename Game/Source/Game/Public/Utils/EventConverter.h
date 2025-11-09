// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EventConverter.generated.h"

struct FCycleDefinition;

UCLASS()
class GAME_API UEventConverter : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static void TriggerCycleEvent(const UObject* WorldContextObject, const FCycleDefinition& CycleDefinition);
};
