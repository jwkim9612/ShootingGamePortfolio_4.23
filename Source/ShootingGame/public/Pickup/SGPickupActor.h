#pragma once

#include "ShootingGame.h"
#include "GameFramework/Actor.h"
#include "SGPickupActor.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPickupDelegate);

UCLASS()
class SHOOTINGGAME_API ASGPickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASGPickupActor();

protected:
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	class USoundBase* PickupSound;

public:
	FOnPickupDelegate OnPickup;
};
