// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/DemonstratorSubsystem.h"
#include "../Public/CollisionDemonstrator.h"
#include "CollisionsSubsystem.generated.h"

/**
 * 
 */	class ACollisionDemonstrator;

UCLASS()
class FG3DMATH_API UCollisionsSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	virtual void Tick(float DeltaTime) override;
	
public:
	UPROPERTY(VisibleAnywhere)
	TArray<ACollisionDemonstrator*> CollisionDemonstrators;
	void RegisterDemonstrator(ACollisionDemonstrator* Demonstrator);
	void UnregisterDemonstrator(ACollisionDemonstrator* Demonstrator);

	virtual TStatId GetStatId() const override;
};
