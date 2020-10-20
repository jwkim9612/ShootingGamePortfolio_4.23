#pragma once

#include "ShootingGame.h"
#include "Level/SGLevelScriptActorBase.h"
#include "SGCave.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API ASGCave : public ASGLevelScriptActorBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
};
