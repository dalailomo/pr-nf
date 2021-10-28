// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Pickup.h"
#include "PickupWeapon.h"
#include "PickupPowerUp.h"
#include "PickupItem.h"
#include "EquippedWeapon.h"

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

void UInventoryComponent::HandleWeaponPick(APickupWeapon* Weapon)
{
	switch (Weapon->GetName())
	{
		case P_Name::PN_Weapon_Crossbow:
			EquippedCrossbow->GetDefaultObject<AEquippedWeapon>()->PickWeapon(Weapon);
			break;

		case P_Name::PN_Weapon_Shotgun:
			EquippedShotgun->GetDefaultObject<AEquippedWeapon>()->PickWeapon(Weapon);
			break;

		case P_Name::PN_Weapon_ThunderFist:
			EquippedThunderFist->GetDefaultObject<AEquippedWeapon>()->PickWeapon(Weapon);
			break;

		case P_Name::PN_Weapon_ObsidianSword:
			EquippedObsidianSword->GetDefaultObject<AEquippedWeapon>()->PickWeapon(Weapon);
			break;

		case P_Name::PN_Weapon_BookOfSun:
			EquippedBookOfSun->GetDefaultObject<AEquippedWeapon>()->PickWeapon(Weapon);
			break;

		case P_Name::PN_Weapon_AbyssStaff:
			EquippedAbyssStaff->GetDefaultObject<AEquippedWeapon>()->PickWeapon(Weapon);
			break;

		case P_Name::PN_Weapon_Ruin:
			EquippedRuin->GetDefaultObject<AEquippedWeapon>()->PickWeapon(Weapon);
			break;
	}
}

void UInventoryComponent::HandlePowerUpPick(APickupPowerUp* PowerUp, APlayerCharacter* PlayerCharacter)
{
}

void UInventoryComponent::HandleItemPick(APickupItem* Item, APlayerCharacter* PlayerCharacter)
{
}

void UInventoryComponent::Pick(APickup* Pickup, APlayerCharacter* PlayerCharacter)
{
	if (Pickup)
	{
		if (APickupWeapon* Weapon = Cast<APickupWeapon>(Pickup))
		{
			HandleWeaponPick(Weapon);
		}
		else if (APickupPowerUp* PowerUp = Cast<APickupPowerUp>(Pickup))
		{
			HandlePowerUpPick(PowerUp, PlayerCharacter);
		}
		else if (APickupItem* Item = Cast<APickupItem>(Pickup))
		{
			HandleItemPick(Item, PlayerCharacter);
		}

		Pickup->Destroy();
	}
}

