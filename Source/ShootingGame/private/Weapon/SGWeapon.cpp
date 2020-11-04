#include "SGWeapon.h"
#include "SGProjectile.h"
#include "PoolService.h"
#include "SGSaveGame.h"
#include "Kismet/KismetMathLibrary.h"

ASGWeapon::ASGWeapon()
{
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	FireAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("FireAudioComponent"));
	ReloadAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ReloadAudioComponent"));

	SetRootComponent(MeshComponent);
	FireAudioComponent->SetupAttachment(RootComponent);
	ReloadAudioComponent->SetupAttachment(RootComponent);

	FireAudioComponent->SetAutoActivate(false);
	ReloadAudioComponent->SetAutoActivate(false);

	ProjectilePool.Reserve(PoolService::ProjectileCount);

	CurrentProjectileIndex = 0;
}

void ASGWeapon::Fire(FVector TargetLocation)
{
	SGCHECK(ProjectileClass);
	
	if (Type == WeaponType::None)
	{
		SGLOG(Warning, TEXT("The type of %s has not been decided"), *GetName());
		return;
	}

	FVector MuzzleLocation = GetMuzzleLocation();
	FRotator MuzzleRotation = GetMuzzleRotation();

	FRotator FinalRotation = UKismetMathLibrary::FindLookAtRotation(MuzzleLocation, TargetLocation);
	FVector LaunchDirection = FinalRotation.Vector();
	if (CurrentProjectileIndex == 10)
	{
		CurrentProjectileIndex = 0;
	}

	auto CurrentProjectile = ProjectilePool[CurrentProjectileIndex];
	CurrentProjectile->SetActorLocation(MuzzleLocation);
	CurrentProjectile->FireInDirection(LaunchDirection);
	CurrentProjectile->Activate();
	PlayFireSound();
	PlayMuzzleFlash();
	UseAmmo();

	++CurrentProjectileIndex;
}

void ASGWeapon::Reload()
{
	if (IsFullAmmo())
		return;

	int32 ReloadValues = ClipSize - Ammo;
	if (ReloadValues > MaxAmmo)
	{
		Ammo += MaxAmmo;
		MaxAmmo = 0;
	}
	else
	{
		MaxAmmo -= ReloadValues;
		Ammo += ReloadValues;
	}

	OnAmmoChanged.Broadcast();
}

void ASGWeapon::UseAmmo()
{
	if (Ammo > 0)
	{
		--Ammo;
		OnAmmoChanged.Broadcast();
	}
}

void ASGWeapon::AddMaxAmmo(int32 IncreaseValue)
{
	MaxAmmo += IncreaseValue;
	OnAmmoChanged.Broadcast();
}

bool ASGWeapon::HasAmmo() const
{
	if (Ammo > 0)
		return true;
	
	return false;
}

bool ASGWeapon::HasMaxAmmo() const
{
	if (MaxAmmo > 0)
		return true;
	
	return false;
}

float ASGWeapon::GetFireRate() const
{
	return FireRate;
}

float ASGWeapon::GetRecoli() const
{
	return Recoli;
}

void ASGWeapon::PlayMuzzleFlash()
{
	SGCHECK(MuzzleFlashParticle);

	FVector MuzzleLocation = GetMuzzleLocation();
	FRotator MuzzleRotation = GetMuzzleRotation();
	auto MuzzleFlash = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlashParticle, MuzzleLocation, MuzzleRotation);
	MuzzleFlash->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
}

bool ASGWeapon::IsFullAmmo() const
{
	if (Ammo == ClipSize)
		return true;
	
	return false;
}

void ASGWeapon::PlayFireSound()
{
	SGCHECK(FireAudioComponent);
	FireAudioComponent->Play();
}

void ASGWeapon::PlayReloadSound()
{
	SGCHECK(ReloadAudioComponent);
	ReloadAudioComponent->Play();
}

void ASGWeapon::SetWeaponData(FSGWeaponData* NewWeaponData)
{
	MaxAmmo = NewWeaponData->MaxAmmo;
	ClipSize = NewWeaponData->ClipSize;
	Ammo = NewWeaponData->Ammo;
	FireRate = NewWeaponData->FireRate;
	Recoli = NewWeaponData->Recoli;
	Type = NewWeaponData->Type;

	FireAudioComponent->SetSound(NewWeaponData->FireAudio);
	ReloadAudioComponent->SetSound(NewWeaponData->ReloadAudio);
	MuzzleFlashParticle = NewWeaponData->MuzzleFlashParticle;
}

void ASGWeapon::SetVisibility(bool bNewVisibility)
{
	MeshComponent->SetVisibility(bNewVisibility);
}

void ASGWeapon::SetController(AController * NewController)
{
	SGCHECK(NewController);
	Controller = NewController;
}

void ASGWeapon::SetControllingPawn(APawn * NewPawn)
{
	SGCHECK(NewPawn);
	ControllingPawn = NewPawn;
}

void ASGWeapon::InitializeAmmo()
{
	auto SGSaveGame = Cast<USGSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerSaveData"), 0));
	if (SGSaveGame != nullptr)
	{
		switch (Type)
		{
		case WeaponType::Rifle:
			Ammo = SGSaveGame->RifleAmmo;
			MaxAmmo = SGSaveGame->RifleMaxAmmo;
			break;
		case WeaponType::Pistol:
			Ammo = SGSaveGame->PistolAmmo;
			MaxAmmo = SGSaveGame->PistolMaxAmmo;
			break;
		}
	}
}

int32 ASGWeapon::GetAmmo() const
{
	return Ammo;
}

int32 ASGWeapon::GetMaxAmmo() const
{
	return MaxAmmo;
}

FVector ASGWeapon::GetMuzzleLocation() const
{
	return MeshComponent->GetSocketLocation(TEXT("Muzzle"));
}

FRotator ASGWeapon::GetMuzzleRotation() const
{
	return MeshComponent->GetSocketRotation(TEXT("Muzzle"));
}

WeaponType ASGWeapon::GetWeaponType() const
{
	return Type;
}

int32 ASGWeapon::GetDamage() const
{
	ASGProjectile* SGProjectile = ProjectileClass->GetDefaultObject<ASGProjectile>();
	return SGProjectile->GetDamage();
}

void ASGWeapon::CreateProjectilePool()
{
	for (int ProjectilePoolIndex = 0; ProjectilePoolIndex < 10; ProjectilePoolIndex++)
	{
		auto Projectile = GetWorld()->SpawnActor<ASGProjectile>(ProjectileClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if (Projectile != nullptr)
		{
			Projectile->SetController(Controller);
			Projectile->SetControllingPawn(ControllingPawn);
			Projectile->Disable();
			ProjectilePool.Push(Projectile);
		}
	}
}
