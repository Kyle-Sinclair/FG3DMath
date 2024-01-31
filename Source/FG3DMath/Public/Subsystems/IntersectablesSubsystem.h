// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemonstratorSubsystem.h"
#include "Subsystems/WorldSubsystem.h"
#include "IntersectablesSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FG3DMATH_API UIntersectablesSubsystem : public UDemonstratorSubsystem
{
	GENERATED_BODY()

public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual void ProcessDemonstrator(ADemonstrator* Registree) override;

};
