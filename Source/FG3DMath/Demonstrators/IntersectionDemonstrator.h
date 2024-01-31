// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IntersectionType.h"
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EIntersectionType> IntersectionType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Sphere")
	float Radius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AABB", meta = (MakeEditWidget = true))
	FVector Min;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AABB", meta = (MakeEditWidget = true))
	FVector Max;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Triangle", meta = (MakeEditWidget = true))
	FVector V0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Triangle", meta = (MakeEditWidget = true))
	FVector V1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Triangle", meta = (MakeEditWidget = true))
	FVector V2;	

	UPROPERTY()
	bool Drawn;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool bIsIntersecting;
	void SetIsIntersecting();
	virtual void Demonstrate() override;
	
};
