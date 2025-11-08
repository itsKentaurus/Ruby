// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "CycleCheatManagerExtension.generated.h"

class UCycleComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogCheatCycle, Log, All);

/**
 * 
 */
UCLASS()
class CYCLE_API UCycleCheatManagerExtension : public UCheatManagerExtension
{
	GENERATED_BODY()

public:
	UCycleCheatManagerExtension();

private:
	// Start Cycle
	UFUNCTION(Exec)
	void Cheat_StartCycle() const;

	// Stop Cycle
	UFUNCTION(Exec)
	void Cheat_StopCycle() const;

	// Reset Cycle
	UFUNCTION(Exec)
	void Cheat_ResetCycle() const;

	// Set multiplier for cycle
	UFUNCTION(Exec)
	void Cheat_SetCycleMultiplier(const float Multiplier) const;

	// Skip to next cycle
	UFUNCTION(Exec)
	void Cheat_SetNextCycle() const;

	UCycleComponent* GetCycleComponent() const;
};
