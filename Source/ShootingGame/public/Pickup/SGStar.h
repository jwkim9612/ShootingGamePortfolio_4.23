#pragma once

#include "ShootingGame.h"
#include "SGPickupActor.h"
#include "SGStar.generated.h"

UCLASS()
class SHOOTINGGAME_API ASGStar : public ASGPickupActor
{
	GENERATED_BODY()
	
public:	
	ASGStar();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
