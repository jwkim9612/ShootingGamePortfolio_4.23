#pragma once

#include "ShootingGame.h"
#include "GameFramework/Actor.h"
#include "SGKey.generated.h"

UCLASS()
class SHOOTINGGAME_API ASGKey : public AActor
{
	GENERATED_BODY()
	
public:	
	ASGKey();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* StaticMeshComponent;
};
