// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Pickup.h"
#include "PickupWeapon.h"
#include "PickupPowerUp.h"
#include "PickupItem.h"
#include "EquippedWeapon.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::HandleWeaponPick(APickupWeapon* PickedWeapon, APlayerCharacter* PlayerCharacter)
{
	TSubclassOf<AEquippedWeapon> FoundEquippedWeaponSubClass = EquippedWeapons[PickedWeapon->GetName()];
	if (!FoundEquippedWeaponSubClass) return;

	AEquippedWeapon* FoundEquippedWeaponClass = FoundEquippedWeaponSubClass->GetDefaultObject<AEquippedWeapon>();
	if (!FoundEquippedWeaponClass) return;

	FoundEquippedWeaponClass->IncrementAmmo(PickedWeapon);

	PlayerCharacter->ReceiveOnWeaponPicked();
}

void UInventoryComponent::HandlePowerUpPick(APickupPowerUp* PickedPowerUp, APlayerCharacter* PlayerCharacter)
{
}

void UInventoryComponent::HandleItemPick(APickupItem* PickedItem, APlayerCharacter* PlayerCharacter)
{
}

void UInventoryComponent::Pick(APickup* PickedActor, APlayerCharacter* PlayerCharacter)
{
	if (!PickedActor) return;
	
	if (APickupWeapon* PickedWeapon = Cast<APickupWeapon>(PickedActor))
	{
		HandleWeaponPick(PickedWeapon, PlayerCharacter);
	}
	else if (APickupPowerUp* PickedPowerUp = Cast<APickupPowerUp>(PickedActor))
	{
		HandlePowerUpPick(PickedPowerUp, PlayerCharacter);
	}
	else if (APickupItem* PickedItem = Cast<APickupItem>(PickedActor))
	{
		HandleItemPick(PickedItem, PlayerCharacter);
	}

	PickedActor->Destroy();
}

