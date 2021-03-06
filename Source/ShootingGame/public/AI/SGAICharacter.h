#pragma once

#include "ShootingGame.h"
#include "AI/SGAICharacterBase.h"
#include "SGAICharacter.generated.h"


UCLASS()
class SHOOTINGGAME_API ASGAICharacter : public ASGAICharacterBase
{
	GENERATED_BODY()

public:
	ASGAICharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Fire(const FVector& TargetLocation) override;

public:
	void SetDead(bool bDead);
	void SetDropAmmoClass(WeaponType Type);
	bool IsDead() const;
	class USGAICharacterAnimInstance* GetAnimInstance() const;

private:
	UFUNCTION()
	void DropItem();

	UFUNCTION()
	void SetDeadCollision();

	UFUNCTION()
	void SetDestroyTimer();

private:
	void CreateWeapon();
	void Dead();

private:
	UPROPERTY(VisibleAnywhere, Category = "AI", meta = (AllowPrivateAccess = true))
	class UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSourceComponent;

	UPROPERTY()
	class ASGAIController* SGAIController;

	UPROPERTY()
	class USGAICharacterAnimInstance* SGAICharacterAnimInstance;

private:
	UPROPERTY(EditAnywhere, category = "DropAmmo", meta = (AllowPrivateAccess = true))
	TSubclassOf<class ASGAmmo> DropAmmo;

	UPROPERTY()
	class ASGWeapon* SGWeapon;

private:
	FTimerHandle DeadTimerHandle;
	bool bIsDead;
};
