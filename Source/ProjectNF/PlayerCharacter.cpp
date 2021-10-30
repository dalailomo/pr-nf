// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "InventoryComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"


/******************************************************* Constructor and engine functions */

// Sets default values
APlayerCharacter::APlayerCharacter() :
	// Base rates
	BaseTurnRate(45.f),
	BaseLookupRate(45.f),

	// Mouselook sensitivity scale factors
	MouseHipTurnRate(1.0f),
	MouseHipLookupRate(1.0f),
	MouseAimingTurnRate(0.4f),
	MouseAimingLookupRate(0.4f),

	// true when aiming
	bAiming(false),

	// Camera FOV values
	CameraDefaultFOV(0.f), // set in BeginPlay
	CameraZoomedFOV(35.f),
	CameraCurrentFOV(0.f), // set in BeginPlay
	ZoomInterpSpeed(20.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the camera and attach it to the root component
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(RootComponent);
	PlayerCamera->bUsePawnControlRotation = true;

	// Create the inventory component
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


/******************************************************* Input bindings */

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	// We have to make sure that string name matches the name of the input mapping in project settings!
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::Lookup);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	/*
	PlayerInputComponent->BindAction("FireButton", IE_Pressed, this, &APlayerCharacter::FireButtonPressed);
	PlayerInputComponent->BindAction("FireButton", IE_Released, this, &APlayerCharacter::FireButtonReleased);

	PlayerInputComponent->BindAction("AimingButton", IE_Pressed, this, &APlayerCharacter::AimingButtonPressed);
	PlayerInputComponent->BindAction("AimingButton", IE_Released, this, &APlayerCharacter::AimingButtonReleased);
	*/
}


/******************************************************* Movement and mouse look */

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find which way is forward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
		AddMovementInput(Direction, Value);

		if (CameraHeadBobbing != nullptr)
		{
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(CameraHeadBobbing, fabs(Value));
		}
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find which way is right
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	// Calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds()); // deg/sec * sec/frame
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// Calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookupRate * GetWorld()->GetDeltaSeconds()); // deg/sec * sec/frame
}

void APlayerCharacter::Turn(float Value)
{
	float TurnScaleFactor{};

	if (bAiming)
	{
		TurnScaleFactor = MouseAimingTurnRate;
	}
	else
	{
		TurnScaleFactor = MouseHipTurnRate;
	}

	AddControllerYawInput(Value * TurnScaleFactor);
}

void APlayerCharacter::Lookup(float Value)
{
	float LookupScaleFactor{};

	if (bAiming)
	{
		LookupScaleFactor = MouseAimingLookupRate;
	}
	else
	{
		LookupScaleFactor = MouseHipLookupRate;
	}

	AddControllerPitchInput(Value * LookupScaleFactor);
}
