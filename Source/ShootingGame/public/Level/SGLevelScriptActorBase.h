#pragma once

#include "ShootingGame.h"
#include "Engine/LevelScriptActor.h"
#include "SGLevelScriptActorBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestCompleteDelegate);

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
	int32 GetObjectiveCount() const;
	int32 GetAttainmentCount() const;
	bool IsQuestComplete() const;

protected:
	UFUNCTION()
	void AddAttainmentCount();

public:
	FOnQuestCompleteDelegate OnQuestComplete;

protected:
	UPROPERTY()
	class USGGameInstance* SGGameInstance;

	UPROPERTY()
	class USGObjectiveHUD* SGObjectiveHUD;

	int32 ObjectiveCount;
	int32 AttainmentCount;
};
