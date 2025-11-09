// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PoolDataTypes.h"
#include "UObject/Interface.h"
#include "PoolActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPoolActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class POOL_API IPoolActorInterface
{
	GENERATED_BODY()

public:
	friend class UPoolSubsystem;

protected:
	TSharedPtr<FActorPool> ActorPool = nullptr;
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;

private:
	FName PoolName;
};
