// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DemonstratorSubsystem.generated.h"

class ADemonstrator;
/**
 * 
 */
UCLASS(Abstract)
class FG3DMATH_API UDemonstratorSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	UPROPERTY()
	TArray<ADemonstrator*> Registrants;

	virtual void RegisterDemonstrator(ADemonstrator* Registree);
	virtual void ProcessDemonstrator(ADemonstrator* Registree);
};
