#pragma once

#include "ShootingGame.h"
#include "SGAICharacterBase.h"
#include "SGBoss.generated.h"

UCLASS()
class SHOOTINGGAME_API ASGBoss : public ASGAICharacterBase
{
	GENERATED_BODY()

public:
	ASGBoss();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual void Fire(const FVector& TargetLocation) override;

private:
	void CreateProjectilePool();

private:
	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (AllowPrivateAccess = true))
	TSubclassOf<class ASGProjectile> ProjectileClass;

	UPROPERTY()
	TArray<class ASGProjectile*> ProjectilePool;


	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (AllowPrivateAccess = true))
	int32 ProjectilePoolSize;
	int32 ProjectileIndex;

};
