#include "SGAmmo.h"
#include "SGPlayer.h"
#include "SGWeapon.h"
#include "AmmoService.h"

ASGAmmo::ASGAmmo()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	StaticMesh->SetCollisionProfileName(TEXT("OverlapOnlyPawnPhysicsActor"));
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ASGAmmo::OnOverlapBegin);
	StaticMesh->SetSimulatePhysics(true);
}

void ASGAmmo::BeginPlay()
{
	Super::BeginPlay();
	
	SetCount();
}

void ASGAmmo::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto SGPlayer = Cast<ASGPlayer>(OtherActor);
	if (SGPlayer != nullptr)
	{
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

void ASGAmmo::SetCount()
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

