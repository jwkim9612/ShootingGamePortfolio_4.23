#pragma once

#include "ShootingGame.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FocusTo.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API UBTTask_FocusTo : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_FocusTo();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
