// Fill out your copyright notice in the Description page of Project Settings.


#include "IntersectionDemonstrator.h"

#include "AITypes.h"
#include "Engine/Engine.h"
#include "FG3DMath/FunctionLibraries/Intersection/DrawShapeUtility.h"
#include "Subsystems/IntersectablesSubsystem.h"


void AIntersectionDemonstrator::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	bIsIntersecting = false;
}

void AIntersectionDemonstrator::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetSubsystem<UIntersectablesSubsystem>()->RegisterDemonstrator(this);
}

void AIntersectionDemonstrator::SetIsIntersecting()
{
	bIsIntersecting = true;
}

void AIntersectionDemonstrator::Demonstrate()
{
	Super::Demonstrate();
	if(bPrintAnyDebugs){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Demonstrator reporting for duty"));
	}

	if(Drawn) return;
	
	//Drawn = true;

	const auto Location = GetActorLocation();
	const auto WorldContext = GetWorld();
	
	switch(IntersectionType.GetValue())
	{
	case EIntersectionType::Sphere:
		UShapeDrawUtility::Sphere(WorldContext, Location, Radius, bIsIntersecting ? FColor::Red : FColor::Blue);
		break;

	case EIntersectionType::Plane:
		UShapeDrawUtility::Plane(WorldContext, Location, GetActorUpVector(), GetActorQuat(),  bIsIntersecting ? FColor::Red : FColor::Blue);
		break;
	
	case EIntersectionType::AABB:
		UShapeDrawUtility::Box(WorldContext, Location, Min, Max,  bIsIntersecting ? FColor::Red : FColor::Blue);
		break;

	case EIntersectionType::Triangle:
		UShapeDrawUtility::Triangle(WorldContext, GetActorTransform(), V0, V1, V2,  bIsIntersecting ? FColor::Red : FColor::Blue);
		break;

	case EIntersectionType::Ray:
		UShapeDrawUtility::Ray(WorldContext, GetActorLocation(), GetActorForwardVector(),  bIsIntersecting ? FColor::Red : FColor::Blue);
		break;		
	}
}


