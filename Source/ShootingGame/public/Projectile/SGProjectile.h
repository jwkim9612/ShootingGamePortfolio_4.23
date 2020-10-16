#pragma once

#include "ShootingGame.h"
#include "GameFramework/Actor.h"
#include "SGProjectile.generated.h"

UCLASS()
class SHOOTINGGAME_API ASGProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASGProjectile();

protected:
	virtual void BeginPlay() override;

public:
	void FireInDirection(const FVector & ShootDirection);

	void Disable();
	void Activate();

	void SetController(AController* NewController);
	void SetControllingPawn(APawn* NewPawn);

	int32 GetDamage() const;

private:
	void SetDisableTimer(float DisableTimer);
	void ClearDisableTimer();

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UParticleSystemComponent* ParticleSystemComponent;

private:
	UPROPERTY()
	class USGGameInstance* SGGameInstance;

	UPROPERTY()
	class AController* Controller;

	UPROPERTY()
	class APawn* ControllingPawn;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	int32 Damage;

	FTimerHandle DisableTimerHandle;
};
