#pragma once

#include "ShootingGame.h"
#include "GameFramework/Character.h"
#include "SGAICharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeadDelegate);

UCLASS()
class SHOOTINGGAME_API ASGAICharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ASGAICharacterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Fire(const FVector& ShootDirection);
	void SetTarget(class ASGPlayer* NewTarget);
	class ASGPlayer* GetTarget() const;
	float GetHPRatio() const;

public:
	FOnDeadDelegate OnDead;

private:
	UPROPERTY()
	class ASGPlayer* Target;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 CurrentHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 MaxHealth;
};
