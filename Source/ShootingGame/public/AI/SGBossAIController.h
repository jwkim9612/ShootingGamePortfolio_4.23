#pragma once

#include "ShootingGame.h"
#include "AIController.h"
#include "SGBossAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API ASGBossAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASGBossAIController();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UBlackboardData* BlackBoardData;

	UPROPERTY()
	class UBehaviorTree* BehaviorTree;

};
