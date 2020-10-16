#pragma once

#include "ShootingGame.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "SGType.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGType : public UObject
{
	GENERATED_BODY()
	
};

enum class CameraMode : uint8
{
	None,
	UnAiming,
	Aiming,
	Stand,
	Crouch
};

UENUM(BlueprintType)
enum class WeaponType : uint8
{
	None,
	Rifle,
	Pistol
};

USTRUCT()
struct SHOOTINGGAME_API FSGParticleData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<class UParticleSystem> ParticlePath;
};

USTRUCT()
struct SHOOTINGGAME_API FSGWeaponData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASGWeapon> Class;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASGProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly)
	int32 ClipSize;

	UPROPERTY(EditDefaultsOnly)
	int32 Ammo;

	UPROPERTY(EditDefaultsOnly)
	float FireRate;

	UPROPERTY(EditDefaultsOnly)
	float Recoli;

	UPROPERTY(EditDefaultsOnly)
	WeaponType Type;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* FireAudio;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* ReloadAudio;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* AmmoPickupAudio;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* MuzzleFlashParticle;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* Image;
};

USTRUCT()
struct SHOOTINGGAME_API FSGImageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<class UTexture2D> ImagePath;
};

USTRUCT()
struct SHOOTINGGAME_API FSGStageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	int32 Id;

	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	FString Description;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* Image;
};
