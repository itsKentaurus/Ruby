// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/PlayingGameState.h"

#include "CycleComponent.h"
#include "Utils/EventConverter.h"

APlayingGameState::APlayingGameState()
{
	CycleComponent = CreateDefaultSubobject<UCycleComponent>("CycleComponent");
}

void APlayingGameState::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(CycleComponent))
	{
		CycleComponent->CycleUpdated.BindUObject(this, &APlayingGameState::OnCycleUpdated);
	}
}

void APlayingGameState::OnCycleUpdated(const FCycleDefinition& CycleDefinition)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *CycleDefinition.ToString());

	UEventConverter::TriggerCycleEvent(this, CycleDefinition);
}
