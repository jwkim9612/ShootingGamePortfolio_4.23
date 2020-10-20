#pragma once

#include "ShootingGame.h"
#include "Level/SGLevelScriptActorBase.h"
#include "SGBunker.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API ASGBunker : public ASGLevelScriptActorBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
};
