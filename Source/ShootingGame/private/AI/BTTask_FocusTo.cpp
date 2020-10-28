#include "BTTask_FocusTo.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_FocusTo::UBTTask_FocusTo()
{
	bCreateNodeInstance = true;
	NodeName = TEXT("FocusTo");
}


EBTNodeResult::Type UBTTask_FocusTo::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;

	UWorld* World = ControllingPawn->GetWorld();
	if (World == nullptr)
		return EBTNodeResult::Failed;

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	if (Target == nullptr)
		return EBTNodeResult::Failed;

	FVector TargetLocation = Target->GetActorLocation();

	float LookYaw = UKismetMathLibrary::FindLookAtRotation(ControllingPawn->GetActorLocation(), TargetLocation).Yaw;
	FRotator ControllingPawnRotator = ControllingPawn->GetActorRotation();
	ControllingPawn->SetActorRelativeRotation(
		FRotator(
			ControllingPawnRotator.Pitch,
			LookYaw,
			ControllingPawnRotator.Roll)
	);

	return Result;
}
