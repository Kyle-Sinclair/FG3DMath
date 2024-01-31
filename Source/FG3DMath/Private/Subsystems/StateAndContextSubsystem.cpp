// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/StateAndContextSubsystem.h"


void UStateAndContextSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UStateAndContextSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TStatId UStateAndContextSubsystem::GetStatId() const
{
	return GetStatID();
}
