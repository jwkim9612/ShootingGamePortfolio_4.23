#pragma once

#include "ShootingGame.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsLessThanHealth.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API UBTDecorator_IsLessThanHealth : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_IsLessThanHealth();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	UPROPERTY(EditAnywhere, Category = "Health", meta = (AllowPrivateAccess = true, UIMin = 0.0f, UIMax = 1.0f, ClampMin = 0.0f, ClampMax = 1.0f))
	float Ratio;
};
