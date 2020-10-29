#include "BTDecorator_TargetOnFireAngle.h"
#include "SGPlayer.h"
#include "SGAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTDecorator_TargetOnFireAngle::UBTDecorator_TargetOnFireAngle()
{
	NodeName = TEXT("TargetOnFireAngle");
}

bool UBTDecorator_TargetOnFireAngle::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	ASGPlayer* Target = Cast<ASGPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (Target == nullptr)
		return false;

	float LookAtYaw = UKismetMathLibrary::FindLookAtRotation(ControllingPawn->GetActorLocation(), Target->GetActorLocation()).Yaw;
	float ControllingPawnYaw = ControllingPawn->GetActorRotation().Yaw;

	int32 Angle = FMath::Abs(LookAtYaw - ControllingPawnYaw);
	if (Angle > 90)
		bResult = false;
	else
		bResult = true;

	return bResult;
}
