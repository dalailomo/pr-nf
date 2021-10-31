// Fill out your copyright notice in the Description page of Project Settings.


#include "EquippedWeapon.h"
#include "PickupWeapon.h"
#include "Pickup.h"

// Sets default values
AEquippedWeapon::AEquippedWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEquippedWeapon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEquippedWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEquippedWeapon::IncrementAmmo(APickupWeapon* PickedWeapon)
{
	Ammo += PickedWeapon->GetAmmoAmount();
}

