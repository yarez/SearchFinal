// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SearchFinal.h"
#include "SearchFinalCharacter.h"
#include "SearchFinalProjectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "SearchObj.h"
#include "IHeadMountedDisplay.h"


DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ASearchFinalCharacter

ASearchFinalCharacter::ASearchFinalCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ASearchFinalCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASearchFinalCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAxis("MoveForward", this, &ASearchFinalCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ASearchFinalCharacter::MoveRight);

	InputComponent->BindAction("Search", IE_Pressed, this, &ASearchFinalCharacter::OnSearch);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ASearchFinalCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ASearchFinalCharacter::LookUpAtRate);
}

void ASearchFinalCharacter::OnSearch()
{
	AActor *hitActor;

	FVector CameraOrigin;
	FQuat OutOrientation;
	float OutHFOV, OutVFOV, OutCameraDistance, OutNearPlane, OutFarPlane;
	GEngine->HMDDevice->GetPositionalTrackingCameraProperties(CameraOrigin, OutOrientation, OutHFOV, OutVFOV, OutCameraDistance, OutNearPlane, OutFarPlane);

	FHitResult *hit = new FHitResult;
	FVector start = FirstPersonCameraComponent->GetComponentLocation();
	//FVector start = CameraOrigin;
	FVector dir = FirstPersonCameraComponent->GetForwardVector();
	FVector end = start + GetControlRotation().Vector() * 150;


	FCollisionQueryParams *traceParams = new FCollisionQueryParams;
	traceParams->bTraceComplex = true;
	traceParams->bTraceAsyncScene = true;
	traceParams->bReturnPhysicalMaterial = false;

	GetWorld()->LineTraceSingleByChannel(*hit, start, end, ECC_Visibility, *traceParams);
	if (hit->bBlockingHit)
	{
		DrawDebugLine(
			GetWorld(),
			start, // Start Trace
			hit->Location, // Hit Result Location
			FColor(255, 0, 0), // Red
			false, // Persistent Lines
			2.0, // Time
			0, // Depth Priority
			2.0 // Thickness
		);

		hitActor = Cast<AActor>(hit->Actor.Get());
		GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Red, "Hit");

		if (hitActor->GetActorLabel().Contains(TEXT("SearchObj"), ESearchCase::IgnoreCase, ESearchDir::FromEnd)) {
			ASearchObj *hitSearchObj = Cast<ASearchObj>(hitActor);
			hitSearchObj->Search();
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Red, "No Hit ");
	}
}

void ASearchFinalCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ASearchFinalCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ASearchFinalCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASearchFinalCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}