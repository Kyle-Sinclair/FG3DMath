// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FG3DMath/Demonstrators/IntersectionDemonstrator.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IntersectionTests.generated.h"

/**
 * 
 */
UCLASS()
class FG3DMATH_API UIntersectionTests : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintCallable, Category = "Intersection Testing")
	static bool CalculateIntersection(AIntersectionDemonstrator* DemonstratorA, FVector Origin, FVector Direction, bool& bIsIntersecting)
	{
		FVector ContactPoint;
		if(DemonstratorA->IntersectionType == EIntersectionType::Sphere)
			bIsIntersecting = RaySphere(Origin, Direction, DemonstratorA->GetActorLocation(),DemonstratorA->Radius,ContactPoint);

		
		return false;
	}

	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool RaySphere(
		const FVector Origin,
		const FVector Direction,
		const FVector Center,
		const float Radius,
		FVector& ContactPoint)
	{
		const auto W = Center - Origin;
		const auto WSQ = W.Dot(W);
		const auto Projection = W.Dot(Direction);
		const auto RSQ = Radius * Radius;

		// If sphere is behind ray, no intersection
		if(Projection < 0.f && WSQ > RSQ)
			return false;

		const auto VSQ = Direction.Dot(Direction);

		// Diff vs radius
		const auto bIntersects = (VSQ * WSQ - Projection * Projection <= VSQ * Radius * Radius);

		if(bIntersects)
		{
			const auto B = 2.f * Projection;
			const auto C = WSQ - Radius * Radius;
			const auto Discriminant = B * B - 4 * VSQ * C;
			const auto T = (B - FMath::Sqrt(Discriminant)) / (2.f * VSQ);

			if(Discriminant < 0)
				ContactPoint = Origin + (Direction * -1.f);
			else
				ContactPoint = Origin + (Direction * T);

			
		}
		
		return bIntersects;
	}
};
