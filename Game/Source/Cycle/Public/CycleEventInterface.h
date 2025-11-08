// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CycleEventInterface.generated.h"

struct FCycleDefinition;
// This class does not need to be modified.
UINTERFACE()
class UCycleEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CYCLE_API ICycleEventInterface
{
	GENERATED_BODY()

public:
	virtual void OnCycleUpdated(const FCycleDefinition& CycleDefinition) = 0;
};
