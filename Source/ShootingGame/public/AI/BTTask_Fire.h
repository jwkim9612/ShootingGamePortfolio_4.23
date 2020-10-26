#pragma once

#include "ShootingGame.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Fire.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API UBTTask_Fire : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Fire();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category = "Fire", meta = (AllowPrivateAccess = true, UIMin = 1, ClampMin = 1))
	int32 Count = 1;

	bool bDone;

	FTimerHandle FireMontageTimerHandle;
};
