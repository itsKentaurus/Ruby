// Fill out your copyright notice in the Description page of Project Settings.


#include "CycleCheatManagerExtension.h"

#include "CycleComponent.h"
#include "GameFramework/GameStateBase.h"

DEFINE_LOG_CATEGORY(LogCheatCycle);

UCycleCheatManagerExtension::UCycleCheatManagerExtension()
{
#if UE_WITH_CHEAT_MANAGER
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		UCheatManager::RegisterForOnCheatManagerCreated(FOnCheatManagerCreated::FDelegate::CreateLambda(
			[](UCheatManager* CheatManager)
			{
				CheatManager->AddCheatManagerExtension(NewObject<ThisClass>(CheatManager));
			}));
	}
#endif
}

void UCycleCheatManagerExtension::Cheat_StartCycle() const
{
	if (auto* CycleComponent = GetCycleComponent(); IsValid(CycleComponent))
	{
		UE_LOG(LogCheatCycle, Log, TEXT("Cheat_StartCycle"));
		CycleComponent->Start();
	}
}

void UCycleCheatManagerExtension::Cheat_StopCycle() const
{
	if (auto* CycleComponent = GetCycleComponent(); IsValid(CycleComponent))
	{
		UE_LOG(LogCheatCycle, Log, TEXT("Cheat_StopCycle"));
		CycleComponent->Stop();
	}
}

void UCycleCheatManagerExtension::Cheat_ResetCycle() const
{
	if (auto* CycleComponent = GetCycleComponent(); IsValid(CycleComponent))
	{
		UE_LOG(LogCheatCycle, Log, TEXT("Cheat_ResetCycle"));
		CycleComponent->Reset();
	}
}

void UCycleCheatManagerExtension::Cheat_SetCycleMultiplier(const float Multiplier) const
{
	if (auto* CycleComponent = GetCycleComponent(); IsValid(CycleComponent))
	{
		UE_LOG(LogCheatCycle, Log, TEXT("Cheat_SetCycleMultiplier %f"), Multiplier);
		CycleComponent->SetMultiplier(Multiplier);
	}
}

void UCycleCheatManagerExtension::Cheat_SetNextCycle() const
{
#if UE_WITH_CHEAT_MANAGER
	if (auto* CycleComponent = GetCycleComponent(); IsValid(CycleComponent))
	{
		UE_LOG(LogCheatCycle, Log, TEXT("Cheat_SkipToNextCycle"));
		CycleComponent->SetNextCycle();
	}
#endif
}

UCycleComponent* UCycleCheatManagerExtension::GetCycleComponent() const
{
	if (const auto* GameState = GetWorld()->GetGameState(); IsValid(GameState))
	{
		auto* CycleComponent = Cast<UCycleComponent>(GameState->GetComponentByClass(UCycleComponent::StaticClass()));
		if (IsValid(CycleComponent))
		{
			return CycleComponent;
		}
	}

	if (const auto* GameMode = GetWorld()->GetAuthGameMode(); IsValid(GameMode))
	{
		auto* CycleComponent = Cast<UCycleComponent>(GameMode->GetComponentByClass(UCycleComponent::StaticClass()));
		if (IsValid(CycleComponent))
		{
			return CycleComponent;
		}
	}

	return nullptr;
}
