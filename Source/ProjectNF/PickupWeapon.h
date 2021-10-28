// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "PickupWeapon.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTNF_API APickupWeapon : public APickup
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float AmmoAmount;

public:
	FORCEINLINE float GetAmmoAmount() { return AmmoAmount; }
	
};
