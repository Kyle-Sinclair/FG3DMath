// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Public/Demonstrator.h"
#include "FG3DMath/FunctionLibraries/Context/ERelativecontext.h"
#include "GameFramework/Character.h"
#include "StateAndContextDemonstrator.generated.h"

/**
 * 
 */
UCLASS()
class FG3DMATH_API AStateAndContextDemonstrator : public ADemonstrator
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Context, meta = (AllowPrivateAccess = "true"))
	APlayerController* CharacterReference;
	
	
	virtual void Tick(float DeltaSeconds) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Demonstrate() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = TestBitflag, meta = (Bitmask, BitmaskEnum = "ERelativeContext"))
	int32 RelativeContext;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = TestBitflag, meta = (Bitmask, BitmaskEnum = "ERelativeContext"))
	int32 ContextKey;
	UFUNCTION(BlueprintNativeEvent)
    void CalculateRelativeContext();
};
