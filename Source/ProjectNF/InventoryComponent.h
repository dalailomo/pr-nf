// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquippedWeapon.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTNF_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEquippedWeapon> EquippedWeapon;

	void HandleWeaponPick(class APickupWeapon* Weapon);
	void HandlePowerUpPick(class APickupPowerUp* PowerUp, class APlayerCharacter* PlayerCharacter);
	void HandleItemPick(class APickupItem* Item, class APlayerCharacter* PlayerCharacter);

public:
	void Pick(class APickup* Pickup, class APlayerCharacter* PlayerCharacter);
};
