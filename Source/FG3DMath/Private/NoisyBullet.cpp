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
	SamplePoint.Y = Remap(0,1000,0,1,SamplePoint.Y);
	SamplePoint.Z = Remap(0,1000,0,1,SamplePoint.Z);
	SampleRange = SamplePoint;
	const FVector noiseValue =  FVector(FMath::PerlinNoise1D(SamplePoint.X),FMath::PerlinNoise1D(SamplePoint.Y),FMath::PerlinNoise1D(SamplePoint.Z));
	Direction = noiseValue;
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
	Direction = NewDirection;

}
float  ANoisyBullet::Remap(float start1, float stop1,float start2, float stop2,float value)
{
	float outgoing = start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
	return outgoing;
}

