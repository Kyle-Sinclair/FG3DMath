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
		if(DemonstratorA->IntersectionType == EIntersectionType::Sphere)
		{
			bIsIntersecting = RaySphere(Origin, Direction, DemonstratorA->GetActorLocation(),DemonstratorA->Radius,DemonstratorA->ContactPoint);
		}
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

	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool RayAABB(
		const FVector Origin,
		const FVector Direction,
		const FVector Min,
		const FVector Max,
		FVector& ContactPoint)
	{
		const auto T1 = (Min.X - Origin.X) / Direction.X;
		const auto T2 = (Max.X - Origin.X) / Direction.X;
		const auto T3 = (Min.Y - Origin.Y) / Direction.Y;
		const auto T4 = (Max.Y - Origin.Y) / Direction.Y;
		const auto T5 = (Min.Z - Origin.Z) / Direction.Z;
		const auto T6 = (Max.Z - Origin.Z) / Direction.Z;

		// Find the largest minimum value
		const auto TMin = FMath::Max(
			FMath::Max(
				FMath::Min(T1,T2),
				FMath::Min(T3,T4)
				),
			FMath::Min(T5,T6)
			);

		// Find the smallest maximum value
		const auto TMax = FMath::Min(
			FMath::Min(
				FMath::Max(T1,T2),
				FMath::Max(T3,T4)
				),
			FMath::Max(T5,T6)
			);

		if(TMax < 0 || TMin > TMax)
			return false;

		const auto T = TMin < 0.f ? TMax : TMin;

		ContactPoint = Origin + (Direction * T);

		return true;
	}

};
