// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DemonstratorSubsystem.h"

#include "Demonstrator.h"
#include "Engine/Engine.h"


void UDemonstratorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Subsystem Online!"));	
}

void UDemonstratorSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (int i = 0; i < Registrants.Num(); i++)
	{
		ProcessDemonstrator(Registrants[i]);
	}
	{
	
	}
}

TStatId UDemonstratorSubsystem::GetStatId() const
{
	return GetStatID();
}

void UDemonstratorSubsystem::RegisterDemonstrator(ADemonstrator* Registree)
{
	Registrants.Add(Registree);
}

void UDemonstratorSubsystem::ProcessDemonstrator(ADemonstrator* Registree)
{
	Registree->Demonstrate();
}
