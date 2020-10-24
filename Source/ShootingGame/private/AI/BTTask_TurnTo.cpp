#include "BTTask_TurnTo.h"
#include "Kismet/KismetMathLibrary.h"
#include "SGAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnTo::UBTTask_TurnTo()
{
	NodeName = TEXT("TurnTo");
}

EBTNodeResult::Type UBTTask_TurnTo::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
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
	
	float LookYaw = UKismetMathLibrary::FindLookAtRotation(ControllingPawn->GetActorLocation(), Target->GetActorLocation()).Yaw;
	FRotator ControllingPawnRotator = ControllingPawn->GetActorRotation();
	ControllingPawn->SetActorRelativeRotation(
		FRotator(
			ControllingPawnRotator.Pitch,
			FMath::FInterpTo(
				ControllingPawnRotator.Yaw,
				LookYaw, World->GetDeltaSeconds(), 
				TurnSpeed),
			ControllingPawnRotator.Roll)
	);

	return Result;
}
