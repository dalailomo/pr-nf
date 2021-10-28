// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UENUM(BlueprintType)
enum class P_Name : uint8
{
	// Weapons
	PN_Weapon_Crossbow			UMETA(DisplayName = "Crossbow"),
	PN_Weapon_Shotgun			UMETA(DisplayName = "Shotgun"),
	PN_Weapon_ThunderFist		UMETA(DisplayName = "Thunder fist"),
	PN_Weapon_ObsidianSword		UMETA(DisplayName = "Obsidian sword"),
	PN_Weapon_BookOfSun			UMETA(DisplayName = "Book of sun"),
	PN_Weapon_AbyssStaff		UMETA(DisplayName = "Abyss staff"),
	PN_Weapon_Ruin				UMETA(DisplayName = "Ruin")
};

UCLASS(Abstract)
class PROJECTNF_API APickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/** Enable item tracing when overlapped */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AreaSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	P_Name Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug", meta = (AllowPrivateAccess = "true"))
	int DebugID;

protected:
	// remember we need UFUNCTION macro for functions used as callbacks
	/** Called when overlapping AreaSphere */
	UFUNCTION()
	void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

public:
	FORCEINLINE P_Name GetName() { return Name; }
	FORCEINLINE int GetDebugID() { return DebugID; }

};
