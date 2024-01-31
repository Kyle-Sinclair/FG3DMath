// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/IntersectablesSubsystem.h"




void UIntersectablesSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UIntersectablesSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TStatId UIntersectablesSubsystem::GetStatId() const
{
	return GetStatID();
}

void UIntersectablesSubsystem::ProcessDemonstrator(ADemonstrator* Registree)
{
	Super::ProcessDemonstrator(Registree);
}
