// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemonstratorSubsystem.h"
#include "FG3DMath/Demonstrators/IntersectionDemonstrator.h"
#include "Subsystems/WorldSubsystem.h"
#include "IntersectablesSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FG3DMATH_API UIntersectablesSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class APlayerCameraManager* PlayerCam = nullptr;
	UPROPERTY()
	TArray<AIntersectionDemonstrator*> Registrants;

	virtual void RegisterDemonstrator(AIntersectionDemonstrator* Registree);
	UPROPERTY()
	FColor NonIntersectingColor = FColor::Blue;
	UPROPERTY()
	FColor IntersectingColor = FColor::Red;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	void CalculateIntersection(AIntersectionDemonstrator* DemonstratorA, FVector Origin, FVector Direction, bool& bIsIntersecting);
	void ProcessDemonstrator(AIntersectionDemonstrator* DemonstratorA);
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	UFUNCTION(BlueprintCallable)
	void ConfigurePlayerCameraReference(APlayerCameraManager* PlayerCamera);

};
