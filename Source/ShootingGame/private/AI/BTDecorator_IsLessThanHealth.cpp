#include "BTDecorator_IsLessThanHealth.h"
#include "SGAICharacterBase.h"
#include "SGBossAIController.h"

UBTDecorator_IsLessThanHealth::UBTDecorator_IsLessThanHealth()
{
	NodeName = TEXT("LessThan");
}

bool UBTDecorator_IsLessThanHealth::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ASGAICharacterBase* ControllingAICharacter = Cast<ASGAICharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingAICharacter == nullptr)
		return false;

	float AIHPRatio = ControllingAICharacter->GetHPRatio();
	if (AIHPRatio <= Ratio)
	{
		bResult = true;
	}
	else
	{
		bResult = false;
	}

	return bResult;
}
