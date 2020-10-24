#pragma once

#include "ShootingGame.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_TurnTo.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API UBTTask_TurnTo : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_TurnTo();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = "Node", meta = (AllowPrivateAccess = true))
	float TurnSpeed;
};
