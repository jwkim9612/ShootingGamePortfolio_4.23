#pragma once

#include "ShootingGame.h"
#include "SGPickupActor.h"
#include "SGType.h"
#include "SGAmmo.generated.h"

UCLASS()
class SHOOTINGGAME_API ASGAmmo : public ASGPickupActor
{
	GENERATED_BODY()
	
public:	
	ASGAmmo();

protected:
	virtual void BeginPlay() override;

private:
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void SetCount();

private:
	UPROPERTY(EditDefaultsOnly, category = "Ammo", meta = (AllowPrivateAccess = true))
	int32 Count;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	WeaponType Type;
};
