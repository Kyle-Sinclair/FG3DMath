// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Bullets.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MotionWarpingComponent.h"
#include "Templates/Tuple.h"

#include "FG3DMathCharacter.generated.h"


UCLASS(config=Game)
class AFG3DMathCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool bShouldVault = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UMotionWarpingComponent* MotionWarpingComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class TSubclassOf<ABullets> BulletPrefab;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UFUNCTION(BlueprintCallable)
	void ToggleVaulting(bool In_bShouldVault);
	UFUNCTION(BlueprintCallable)
	void FindVaultables(bool& bFoundObjectToVaultOver, float I_InitialTraceLength, bool In_DoDebugTraces, FVector& HitLocation);


	FVector GetGroundLocation(const FVector& Vector, bool In_DoDebugTraces);
	UFUNCTION(BlueprintCallable)
	void CalculateVaultObjectLength(bool& bObjectIsOfVaultableLength, int In_MaxVaultLengthLoopCount, float In_CheckRadius, float In_SecondaryTraceGap, float
	                                In_LandingPositionForwardOffset, FVector TestDirection, float& VaultLength,
	                                bool In_DoDebugTraces, FVector HitLocation, FVector& VaultStart, FVector& VaultHeight, FVector& VaultEnd);

	
	UFUNCTION(BlueprintCallable)
	void Vault();
public:
	AFG3DMathCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void Shoot();
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

