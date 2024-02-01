// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Demonstrator.h"
#include "Components/SphereComponent.h"
#include "CollisionDemonstrator.generated.h"

UENUM(Blueprintable)
enum ECollisionType
{
	PlaneCollider,
	SphereCollider
};

/**
 * 
 */
UCLASS()
class FG3DMATH_API ACollisionDemonstrator : public ADemonstrator
{
	GENERATED_BODY()

	
	UPROPERTY()
	USphereComponent* SphereComponent;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ECollisionType> CollisionType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Mass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MoveSpeed;
	

	ACollisionDemonstrator();
	void BeginPlay();
	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

	void AddForce(const FVector& Force);
	void Step(const float DeltaTime);

	float GetRadius() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ApplyGravity;

	UPROPERTY()
	FVector Acceleration;

	UPROPERTY()
	FVector Velocity;
};
