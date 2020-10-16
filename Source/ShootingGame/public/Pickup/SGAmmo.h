#pragma once

#include "ShootingGame.h"
#include "GameFramework/Actor.h"
#include "SGType.h"
#include "SGAmmo.generated.h"

UCLASS()
class SHOOTINGGAME_API ASGAmmo : public AActor
{
	GENERATED_BODY()
	
public:	
	ASGAmmo();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetCount();

private:
	UPROPERTY(VisibleAnywhere, category = "Ammo" ,meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, category = "Ammo", meta = (AllowPrivateAccess = true))
	int32 Count;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	WeaponType Type;
};
