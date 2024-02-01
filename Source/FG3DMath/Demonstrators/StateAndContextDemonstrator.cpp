// Fill out your copyright notice in the Description page of Project Settings.


#include "StateAndContextDemonstrator.h"

#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/StateAndContextSubsystem.h"


void AStateAndContextDemonstrator::CalculateRelativeContext_Implementation()
{
	
}

void AStateAndContextDemonstrator::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AStateAndContextDemonstrator::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetSubsystem<UStateAndContextSubsystem>()->RegisterDemonstrator(this);
	CharacterReference =  UGameplayStatics::GetPlayerController(GetWorld(), 0);
	int BitKey = FMath::RandRange(1, 6);

	ContextKey = 1 << BitKey;
}

void AStateAndContextDemonstrator::Demonstrate()
{
	Super::Demonstrate();
	if(bPrintAnyDebugs){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Demonstrator reporting for duty"));
	}
	CalculateRelativeContext();

}
