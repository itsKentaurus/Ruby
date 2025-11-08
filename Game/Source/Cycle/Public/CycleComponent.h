// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CycleDataTypes.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CheatManagerDefines.h"
#include "CycleComponent.generated.h"

class UCycleSettings;
DECLARE_LOG_CATEGORY_EXTERN(LogCycle, Log, All);

DECLARE_DELEGATE_OneParam(FCycleUpdated, const FCycleDefinition& CycleDefinition);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CYCLE_API UCycleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
#if UE_WITH_CHEAT_MANAGER
	friend class UCycleCheatManagerExtension;
#endif
	
	FCycleUpdated CycleUpdated;
	
	UCycleComponent();

	void Start();
	void Stop();
	void Reset();
	void SetMultiplier(const float Multiplier);
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(Transient)
	TObjectPtr<const UCycleSettings> Settings = nullptr;
	
	FCycleDefinition CurrentCycleDefinition;

	void SetNextCycle();
};
