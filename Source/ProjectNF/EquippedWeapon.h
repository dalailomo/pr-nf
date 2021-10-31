// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquippedWeapon.generated.h"

UENUM(BlueprintType)
enum class EW_DamageType : uint8
{
	EWDT_Blood		UMETA(DisplayName = "Blood"),
	EWDT_Piercing	UMETA(DisplayName = "Piercing"),
	EWDT_Air		UMETA(DisplayName = "Air"),
	EWDT_Earth		UMETA(DisplayName = "Earth"),
	EWDT_Fire		UMETA(DisplayName = "Fire"),
	EWDT_Water		UMETA(DisplayName = "Water"),
	EWDT_ALL		UMETA(DisplayName = "All")
};

UCLASS()
class PROJECTNF_API AEquippedWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEquippedWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/** Firing rate measured in projectiles per minute */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float FiringRate;

	/** Amount of dices used for damage */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float DiceAmount;

	/** Amount of sides of the dice */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float DiceSides;

	/** Damage multiplier for dice result */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float DiceDamageMultiplier;

	/** Ammo amount */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	int Ammo;

	/**Damage type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	EW_DamageType DamageType;

public:
	void IncrementAmmo(class APickupWeapon* Weapon);
};
