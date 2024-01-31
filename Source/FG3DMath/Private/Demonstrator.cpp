// Fill out your copyright notice in the Description page of Project Settings.


#include "Demonstrator.h"

// Sets default values
ADemonstrator::ADemonstrator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
}

// Called when the game starts or when spawned
void ADemonstrator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADemonstrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADemonstrator::Demonstrate()
{
}


