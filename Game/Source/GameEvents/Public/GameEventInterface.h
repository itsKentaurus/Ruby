// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "GameEventInterface.generated.h"

struct FGameEventData;

// This class does not need to be modified.
UINTERFACE()
class UGameEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEEVENTS_API IGameEventInterface
{
	GENERATED_BODY()

public:
	virtual void OnEventTriggered(const FGameEventData& EventData) = 0;
};
