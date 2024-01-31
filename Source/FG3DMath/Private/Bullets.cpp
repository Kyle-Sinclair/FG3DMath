// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullets.h"

#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/Color.h"

// Sets default values
ABullets::ABullets()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BulletBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	
}

// Called when the game starts or when spawned
void ABullets::BeginPlay()
{
	Super::BeginPlay();
	BulletBodyMaterialInstance = UMaterialInstanceDynamic::Create(BulletBody->GetMaterial(0), NULL);
	BulletBody->SetMaterial(0,BulletBodyMaterialInstance);

}

void ABullets::InterpolateValues()
{
	float InterpolatedValue = Age / InterpolationPeriod;
	float RValue = (1-InterpolatedValue) * StartingColor.R + InterpolatedValue * FinalColor.R;
	float GValue = (1-InterpolatedValue) * StartingColor.G + InterpolatedValue * FinalColor.G;
	float BValue = (1-InterpolatedValue) * StartingColor.B + InterpolatedValue * FinalColor.B;
	FColor NewColor = FColor(RValue,GValue,BValue);
	CurrentColor = NewColor;
	BulletBodyMaterialInstance->SetVectorParameterValue("BaseColor",NewColor);

	CurrentSpeed = (1-InterpolatedValue) * StartingSpeed + InterpolatedValue * FinalSpeed;
}

// Called every frame
void ABullets::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Age += DeltaTime;
	if(Age <= InterpolationPeriod)
	{
		InterpolateValues();
	}
	FVector DeltaLocation = Direction * CurrentSpeed * DeltaTime;
	AddActorWorldOffset(DeltaLocation,false);
}

void ABullets::ConfigureOnSpawn(const FVector NewDirection)
{
	Direction = NewDirection;
}

