#pragma once

#include "ShootingGame.h"
#include "GameFramework/Actor.h"
#include "SGWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAmmoChangedDelegate);

UCLASS()
class SHOOTINGGAME_API ASGWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASGWeapon();

protected:
	virtual void BeginPlay() override;

public:
	void Fire(FVector TargetLocation);
	void Reload();
	void UseAmmo();
	void AddMaxAmmo(int32 IncreaseValue);
	bool HasAmmo() const;
	bool HasMaxAmmo() const;
	float GetFireRate() const;
	float GetRecoli() const;
	void PlayMuzzleFlash();
	bool IsFullAmmo() const;
	void PlayFireSound();
	void PlayReloadSound();
	void PlayAmmoPickupSound();

	void SetWeaponData(struct FSGWeaponData* NewWeaponData);
	void SetVisibility(bool bNewVisibility);
	void SetController(AController* NewController);
	void SetControllingPawn(APawn* NewPawn);

	int32 GetAmmo() const;
	int32 GetMaxAmmo() const;
	FVector GetMuzzleLocation() const;
	WeaponType GetWeaponType() const;
	int32 GetDamage() const;

	void CreateProjectilePool();

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UAudioComponent* FireAudioComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UAudioComponent* ReloadAudioComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UAudioComponent* AmmoPickupAudioComponent;

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

	UPROPERTY()
	class AController* Controller;

	UPROPERTY()
	class APawn* ControllingPawn;

private:
	FVector MuzzleLocation;
	FRotator MuzzleRotation;

public:
	FOnAmmoChangedDelegate OnAmmoChanged;
};
