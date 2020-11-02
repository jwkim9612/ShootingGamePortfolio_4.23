#pragma once

#include "ShootingGame.h"
#include "GameFramework/Actor.h"
#include "SGWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAmmoChangedDelegate);

UCLASS()
class SHOOTINGGAME_API ASGWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASGWeapon();

public:
	void Fire(FVector TargetLocation);
	void Reload();
	void UseAmmo();
	void AddMaxAmmo(int32 IncreaseValue);
	bool HasAmmo() const;
	bool HasMaxAmmo() const;
	bool IsFullAmmo() const;
	void PlayMuzzleFlash();
	void PlayFireSound();
	void PlayReloadSound();
	void InitializeAmmo();
	void CreateProjectilePool();

public:
	void SetWeaponData(struct FSGWeaponData* NewWeaponData);
	void SetVisibility(bool bNewVisibility);
	void SetController(AController* NewController);
	void SetControllingPawn(APawn* NewPawn);
	float GetFireRate() const;
	float GetRecoli() const;
	int32 GetAmmo() const;
	int32 GetMaxAmmo() const;
	FVector GetMuzzleLocation() const;
	FRotator GetMuzzleRotation() const;
	WeaponType GetWeaponType() const;
	int32 GetDamage() const;

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UAudioComponent* FireAudioComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UAudioComponent* ReloadAudioComponent;

	UPROPERTY(VisibleAnywhere, category = "bullet", meta = (AllowPrivateAccess = true))
	TSubclassOf<class ASGProjectile> ProjectileClass;

	UPROPERTY(VisibleAnywhere, Category = "bullet", meta = (AllowPrivateAccess = true))
	UParticleSystem* MuzzleFlashParticle;

private:
	UPROPERTY(VisibleAnywhere, Category = "bullet", meta = (AllowPrivateAccess = true))
	int32 MaxAmmo;

	UPROPERTY(VisibleAnywhere, Category = "bullet", meta = (AllowPrivateAccess = true))
	int32 ClipSize;

	UPROPERTY(VisibleAnywhere, Category = "bullet", meta = (AllowPrivateAccess = true))
	int32 Ammo;

	UPROPERTY(VisibleAnywhere, Category = "bullet", meta = (AllowPrivateAccess = true))
	float FireRate;

	UPROPERTY(VisibleAnywhere, Category = "bullet", meta = (AllowPrivateAccess = true))
	float Recoli;

	UPROPERTY(VisibleAnywhere, Category = "Weapon", meta = (AllowPrivateAccess = true))
	WeaponType Type;

private:
	UPROPERTY(VisibleAnywhere, Category = "bullet", meta = (AllowPrivateAccess = true))
	int CurrentProjectileIndex;

	UPROPERTY()
	TArray<class ASGProjectile*> ProjectilePool;

private:
	UPROPERTY()
	class AController* Controller;

	UPROPERTY()
	class APawn* ControllingPawn;

public:
	FOnAmmoChangedDelegate OnAmmoChanged;
};
