// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Public/Demonstrator.h"
#include "IntersectionDemonstrator.generated.h"

/**
 * 
 */
UCLASS()
class FG3DMATH_API AIntersectionDemonstrator : public ADemonstrator
{
	GENERATED_BODY()
	
	virtual void Tick(float DeltaSeconds) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Demonstrate() override;

};
