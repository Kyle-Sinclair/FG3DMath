// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/IntersectablesSubsystem.h"

#include "Camera/CameraComponent.h"
#include "Components/DrawFrustumComponent.h"
#include "FG3DMath/Demonstrators/IntersectionType.h"
#include "FG3DMath/FunctionLibraries/Intersection/DrawShapeUtility.h"
#include "FG3DMath/FunctionLibraries/Intersection/IntersectionTests.h"


void UIntersectablesSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UIntersectablesSubsystem::CalculateIntersection(AIntersectionDemonstrator* DemonstratorA, FVector Origin, FVector Direction, bool& bIsIntersecting)
{
	UIntersectionTests::CalculateIntersection(DemonstratorA,Origin, Direction, bIsIntersecting);
}

void UIntersectablesSubsystem::ProcessDemonstrator(AIntersectionDemonstrator* DemonstratorA)
{
	bool bIsIntersecting = false;
	if(PlayerCam != nullptr)
	{
		FVector Origin = PlayerCam->GetCameraLocation();
		FVector Direction = PlayerCam->GetCameraRotation().Vector();
		UShapeDrawUtility::Ray(PlayerCam->GetWorld(),Origin,Direction,FColor::Blue);
		CalculateIntersection(DemonstratorA,Origin,Direction, bIsIntersecting);
		if(bIsIntersecting)
		{
			DemonstratorA->SetIsIntersecting();
		}
	}
	DemonstratorA->Demonstrate();
}

void UIntersectablesSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for(const auto DemonstratorA : Registrants)
	{
		
		ProcessDemonstrator(DemonstratorA);
	}
}

TStatId UIntersectablesSubsystem::GetStatId() const
{
	return GetStatID();
}

void UIntersectablesSubsystem::RegisterDemonstrator(AIntersectionDemonstrator* Registree)
{
	Registrants.Add(Registree);
}



void UIntersectablesSubsystem::ConfigurePlayerCameraReference(APlayerCameraManager* PlayerCamera)
{
	PlayerCam = PlayerCamera;
	
}