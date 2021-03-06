#pragma once

#include "ShootingGame.h"
#include "SGPickupActor.h"
#include "SGKey.generated.h"

UCLASS()
class SHOOTINGGAME_API ASGKey : public ASGPickupActor
{
	GENERATED_BODY()
	
public:	
	ASGKey();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
