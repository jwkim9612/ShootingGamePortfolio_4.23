#pragma once

#include "ShootingGame.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_TurnToLocation.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API UBTTask_TurnToLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_TurnToLocation();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category = "Turn", meta = (AllowPrivateAccess = true))
	float TurnSpeed;

	UPROPERTY()
	APawn* ControllingPawn;

};
