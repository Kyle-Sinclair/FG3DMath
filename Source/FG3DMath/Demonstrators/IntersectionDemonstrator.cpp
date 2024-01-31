// Fill out your copyright notice in the Description page of Project Settings.


#include "IntersectionDemonstrator.h"

#include "Engine/Engine.h"
#include "Subsystems/IntersectablesSubsystem.h"


void AIntersectionDemonstrator::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AIntersectionDemonstrator::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetSubsystem<UIntersectablesSubsystem>()->RegisterDemonstrator(this);
}

void AIntersectionDemonstrator::Demonstrate()
{
	Super::Demonstrate();
	if(bPrintAnyDebugs){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Demonstrator reporting for duty"));
	}

}
