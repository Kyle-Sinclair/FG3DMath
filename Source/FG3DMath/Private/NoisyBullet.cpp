// Fill out your copyright notice in the Description page of Project Settings.


#include "NoisyBullet.h"

#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ANoisyBullet::ANoisyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BulletBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
}

// Called when the game starts or when spawned
void ANoisyBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANoisyBullet::SampleNoise()
{
	FVector SamplePoint = GetActorLocation();
	SamplePoint.X = Remap(0,1000,0,1,SamplePoint.X);
	SamplePoint.Y = Remap(0,1000,0,1,SamplePoint.X);
	SamplePoint.Z = Remap(0,1000,0,1,SamplePoint.X);
	const float noiseValue = FMath::PerlinNoise3D(FVector(SamplePoint.X,SamplePoint.Y,SamplePoint.Z));
	Speed = FMath::Lerp(MinSpeed,MaxSpeed,noiseValue);	
}

// Called every frame
void ANoisyBullet::Tick(float DeltaTime)
{
	SampleNoise();
	FVector DeltaLocation = Speed * Direction * DeltaTime;
	AddActorLocalOffset(DeltaLocation);
}

void ANoisyBullet::ConfigureOnSpawn(const FVector NewDirection)
{
}
float  ANoisyBullet::Remap(const float Min, const float Max, const float newMin, const float newMax, const float interval)
{
	return ( interval - Min ) / ( Max - Min ) * (newMax - newMin) + newMin;
}

