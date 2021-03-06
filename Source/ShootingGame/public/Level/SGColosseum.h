#pragma once

#include "ShootingGame.h"
#include "Level/SGLevelScriptActorBase.h"
#include "SGColosseum.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API ASGColosseum : public ASGLevelScriptActorBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

private:
	void SetFadeInBossHPBarAnimationTimer();
	
	UFUNCTION()
	void PlayGameClearAnimation();

	UFUNCTION()
	void DeleteSaveData();

	FTimerHandle FadeInBossHPBarTimerHandle;
};
