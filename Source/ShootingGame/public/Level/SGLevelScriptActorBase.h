#pragma once

#include "ShootingGame.h"
#include "Engine/LevelScriptActor.h"
#include "SGLevelScriptActorBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnQuestCompleteDelegate);

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
	UPROPERTY(EditDefaultsOnly, Category = "Quest", meta = (AllowPrivateAccess = true))
	FString QuestText;

protected:
	UPROPERTY()
	class USGGameInstance* SGGameInstance;

	UPROPERTY()
	class USGObjectiveHUD* SGObjectiveHUD;

	UPROPERTY()
	class ASGPlayerController* SGPlayerController;

protected:
	int32 ObjectiveCount;
	int32 AttainmentCount;
};
