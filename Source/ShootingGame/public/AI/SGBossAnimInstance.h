#pragma once

#include "ShootingGame.h"
#include "Animation/AnimInstance.h"
#include "SGBossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	void SetDead();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	bool bIsDead;
};
