#pragma once

#include "ShootingGame.h"
#include "Level/SGLevelScriptActorBase.h"
#include "SGCity.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API ASGCity : public ASGLevelScriptActorBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
};
