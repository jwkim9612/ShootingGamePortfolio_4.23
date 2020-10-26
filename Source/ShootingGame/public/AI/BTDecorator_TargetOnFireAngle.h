#pragma once

#include "ShootingGame.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_TargetOnFireAngle.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API UBTDecorator_TargetOnFireAngle : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTDecorator_TargetOnFireAngle();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
