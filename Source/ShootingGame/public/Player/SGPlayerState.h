#pragma once

#include "ShootingGame.h"
#include "GameFramework/PlayerState.h"
#include "SGPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API ASGPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ASGPlayerState();

public:
	void InitPlayerData(class ASGPlayer* Player);
	void SavePlayerData();
	void SetHPToDamage(int32 Damage);
	void SetHP(int32 NewHP);
	float GetHPRatio() const;
	bool IsMaxHP() const;
	void HealHP();

public:
	FOnHPChangedDelegate OnHPChanged;
	FOnHPIsZeroDelegate OnHPIsZero;

private:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	int32 MaxHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	int32 CurrentHP;

private:
	UPROPERTY()
	class ASGPlayer* SGPlayer;
};
