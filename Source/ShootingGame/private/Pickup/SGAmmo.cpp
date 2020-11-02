#include "SGAmmo.h"
#include "SGPlayer.h"
#include "SGWeapon.h"
#include "AmmoService.h"

ASGAmmo::ASGAmmo()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -25.0f));
	StaticMeshComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	StaticMeshComponent->SetCollisionProfileName(TEXT("Pickup"));
	StaticMeshComponent->SetSimulatePhysics(true);

	CapsuleComponent->SetCapsuleHalfHeight(30.0f);
	CapsuleComponent->SetCapsuleRadius(30.0f);
}

void ASGAmmo::BeginPlay()
{
	Super::BeginPlay();
	
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ASGAmmo::OnOverlapBegin);

	InitializeCount();
}

void ASGAmmo::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto SGPlayer = Cast<ASGPlayer>(OtherActor);
	if (SGPlayer != nullptr)
	{
		Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

		switch (Type)
		{
		case WeaponType::Pistol:
			SGPlayer->GetPistol()->AddMaxAmmo(Count);
			break;
		case WeaponType::Rifle:
			SGPlayer->GetRifle()->AddMaxAmmo(Count);
			break;
		}

		Destroy();
	}
}

void ASGAmmo::InitializeCount()
{
	if (Count == 0)
	{
		switch (Type)
		{
		case WeaponType::Rifle:
			Count = FMath::RandRange(AmmoService::RandomMinCountOfRifle, AmmoService::RandomMaxCountOfRifle);
			break;
		case WeaponType::Pistol:
			Count = FMath::RandRange(AmmoService::RandomMinCountOfPistol, AmmoService::RandomMaxCountOfPistol);
			break;
		}
	}
}
