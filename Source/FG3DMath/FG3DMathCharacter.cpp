// Copyright Epic Games, Inc. All Rights Reserved.

#include "FG3DMathCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DrawDebugHelpers.h"
#include "Subsystems/IntersectablesSubsystem.h"


//////////////////////////////////////////////////////////////////////////
// AFG3DMathCharacter


AFG3DMathCharacter::AFG3DMathCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarp"));


	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AFG3DMathCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFG3DMathCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFG3DMathCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFG3DMathCharacter::Look);

	}

}

void AFG3DMathCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AFG3DMathCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFG3DMathCharacter::Shoot()
{
	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 50;
	FActorSpawnParameters SpawnParameters;
	ABullets* NewBullet = GetWorld()->SpawnActor<ABullets>(BulletPrefab,SpawnLocation,GetActorRotation(),SpawnParameters);
	NewBullet->ConfigureOnSpawn(GetActorForwardVector());
}


void AFG3DMathCharacter::ToggleVaulting(bool In_bShouldVault)
{
	bShouldVault = In_bShouldVault;
}

void AFG3DMathCharacter::FindVaultables(bool& bFoundObjectToVaultOver,float I_InitialTraceLength, bool In_DoDebugTraces, FVector& HitLocation)
{
	if(!bShouldVault)
	{
		bFoundObjectToVaultOver = false;
		return;
	}
	
	FHitResult Outhit;
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * I_InitialTraceLength;
	FCollisionQueryParams CollisionParameters;
	FCollisionResponseParams ResponseParams;
	CollisionParameters.bDebugQuery = In_DoDebugTraces;
	GetWorld()->LineTraceSingleByChannel(Outhit,TraceStart,TraceEnd,ECC_Visibility,CollisionParameters,ResponseParams);

	if(In_DoDebugTraces)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Outhit.bBlockingHit ? FColor::Red : FColor::Green, false, 1, 0, 1);
	}

	bFoundObjectToVaultOver = Outhit.bBlockingHit;
	HitLocation = Outhit.Location;
	
}

FVector AFG3DMathCharacter::GetGroundLocation(const FVector& EmptyGap,bool In_DoDebugTraces)
{
	FHitResult Outhit;
	FVector TraceStart = EmptyGap;
	FVector TraceEnd = EmptyGap + GetActorUpVector() * -200;
	FCollisionQueryParams CollisionParameters;
	FCollisionResponseParams ResponseParams;
	CollisionParameters.bDebugQuery = In_DoDebugTraces;
	GetWorld()->LineTraceSingleByChannel(Outhit,TraceStart,TraceEnd,ECC_Visibility,CollisionParameters,ResponseParams);
	return Outhit.Location;

}

void AFG3DMathCharacter::CalculateVaultObjectLength(bool& bObjectIsOfVaultableLength, int In_MaxVaultLengthLoopCount, float In_CheckRadius,
                                                    float In_SecondaryTraceGap, float In_LandingPositionForwardOffset, FVector TestDirection, float& VaultLength,
                                                    bool In_DoDebugTraces, FVector HitLocation,FVector& VaultStart, FVector& VaultMiddle, FVector& VaultEnd)
{
	bObjectIsOfVaultableLength = false;
	float VaultDistance = 0.0;
	FVector TraceStarts = HitLocation  + GetActorUpVector() * 50;
	FVector TraceEnds = HitLocation  + GetActorUpVector() * -50; ;
	VaultStart = GetActorLocation()  + GetActorForwardVector() * 50;;
		//((HitLocation + GetActorLocation())/2) - GetActorUpVector() * -50;

	FCollisionQueryParams Params;
	FHitResult OutHit;
	TArray<AActor*> ActorsToIgnore;

	EDrawDebugTrace::Type DebugType = In_DoDebugTraces ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None;
	for(int i = 0; i < In_MaxVaultLengthLoopCount;i++)
	{
		//Can extract all info we need from inside this loop
		TraceStarts += GetActorForwardVector() * In_SecondaryTraceGap;
		TraceEnds += GetActorForwardVector() * In_SecondaryTraceGap;
		UKismetSystemLibrary::SphereTraceSingle(GetWorld(),TraceStarts, TraceEnds,In_CheckRadius,TraceTypeQuery1,false,ActorsToIgnore,DebugType, OutHit,true);
		if(!OutHit.bBlockingHit && i > 0)
		{
			FVector GroundLocation = GetGroundLocation(TraceStarts + GetActorForwardVector() * In_LandingPositionForwardOffset,In_DoDebugTraces);;
			
			VaultEnd = GroundLocation + GetActorUpVector() * -25;
			VaultMiddle = (VaultStart + VaultEnd)/2 ;//+ GetActorUpVector() * 50;
			bObjectIsOfVaultableLength = true;
			break;
		}
	}
	if(In_DoDebugTraces)
		{
		DrawDebugLine(GetWorld(),VaultStart,VaultStart + GetActorUpVector() * 50,FColor::Blue,false, 0.1,0,2);
		DrawDebugLine(GetWorld(),VaultEnd,VaultEnd + GetActorUpVector() * 50,FColor::Blue,false, 0.1,0,2);

		}
	
}

void AFG3DMathCharacter::Vault()
{
}


