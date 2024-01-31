// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define TEST_BIT(Bitmask, Bit) (((Bitmask) & (1 << Bit)) > 0)
#define SET_BIT(Bitmask, Bit) (Bitmask |= 1 << static_cast<uint32>(Bit))
#define CLEAR_BIT(Bitmask, Bit) (Bitmask &= ~(1 << static_cast<uint32>(Bit)))

#include "CoreMinimal.h"
#include "ERelativecontext.h"
#include "../Constants.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpatialContextLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FG3DMATH_API USpatialContextLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "Context", meta = ( DefaultToSelf = Target ))
	static int32 GetRelativeContext(const AActor* Target, const AActor* Other)
	{
		int32 ReturnContext = 0;

		const auto TargetLocation = Target->GetActorLocation();
		const auto OtherLocation = Other->GetActorLocation();
		const auto Direction = OtherLocation - TargetLocation;

		const auto LocalSpaceLocation = Target->GetActorTransform().InverseTransformPosition(OtherLocation);

		if(LocalSpaceLocation.X > 0)
			SET_BIT(ReturnContext,ERelativeContext::InFront);
		else if(LocalSpaceLocation.X < 0)
			SET_BIT(ReturnContext,ERelativeContext::Behind);
		
		if(LocalSpaceLocation.Y > 0)
			SET_BIT(ReturnContext,ERelativeContext::ToTheRight);

		
		else if(LocalSpaceLocation.Y < 0)
			SET_BIT(ReturnContext,ERelativeContext::ToTheLeft);

		
		if(LocalSpaceLocation.Z > 0)
			SET_BIT(ReturnContext,ERelativeContext::Above);
			
		else if(LocalSpaceLocation.Z < 0)
			SET_BIT(ReturnContext,ERelativeContext::Below);
		
		return ReturnContext;
	}

	UFUNCTION(BlueprintCallable, Category = "Context")
	static bool TestRelativeContext (const int32 Bitmask,const int32 Context)
	{
		return Bitmask & Context;

	}
};
