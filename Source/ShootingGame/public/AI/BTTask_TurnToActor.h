#pragma once

#include "ShootingGame.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_TurnToActor.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API UBTTask_TurnToActor : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_TurnToActor();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	float Get180DegreeTo360Degree(float ValueToConvert);

private:
	UPROPERTY(EditAnywhere, Category = "Turn", meta = (AllowPrivateAccess = true))
	float TurnSpeed;

	UPROPERTY()
	APawn* ControllingPawn;
};
