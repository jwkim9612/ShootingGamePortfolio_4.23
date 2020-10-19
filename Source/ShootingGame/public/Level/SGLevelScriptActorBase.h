#pragma once

#include "ShootingGame.h"
#include "Engine/LevelScriptActor.h"
#include "SGLevelScriptActorBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API ASGLevelScriptActorBase : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	class USGGameInstance* SGGameInstance;
};
