// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CycleEventInterface.h"
#include "GameFramework/GameStateBase.h"
#include "PlayingGameState.generated.h"

class UCycleComponent;

/**
 * 
 */
UCLASS()
class GAME_API APlayingGameState : public AGameStateBase, public ICycleEventInterface
{
	GENERATED_BODY()

public:
	APlayingGameState();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UCycleComponent> CycleComponent = nullptr;

	virtual void OnCycleUpdated(const FCycleDefinition& CycleDefinition) override;
};
