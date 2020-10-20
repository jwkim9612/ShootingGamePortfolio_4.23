#pragma once

#include "ShootingGame.h"
#include "GameFramework/Character.h"
#include "SGAICharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeadDelegate);

UCLASS()
class SHOOTINGGAME_API ASGAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASGAICharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	void SetDead(bool bDead);
	bool IsDead() const;

private:
	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);

	void DropItem();
	void Dead();

public:
	FOnDeadDelegate OnDead;

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UPawnSensingComponent* PawnSensing;

	UPROPERTY()
	class ASGAIController* SGAIController;

private:
	UPROPERTY(EditAnywhere, category = "Stat", meta = (AllowPrivateAccess = true))
	int32 Health;

	UPROPERTY(EditAnywhere, category = "DropAmmo", meta = (AllowPrivateAccess = true))
	TSubclassOf<class ASGAmmo> DropAmmo;

private:
	FTimerHandle DeadTimerHandle;

	bool bIsDead;
};
