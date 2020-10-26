#include "BTTask_TurnTo.h"
#include "Kismet/KismetMathLibrary.h"
#include "SGAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnTo::UBTTask_TurnTo()
{
	bNotifyTick = true;
	bCreateNodeInstance = true;
	NodeName = TEXT("TurnTo");
}

EBTNodeResult::Type UBTTask_TurnTo::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;

	World = ControllingPawn->GetWorld();
	if (World == nullptr)
		return EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}

void UBTTask_TurnTo::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	TargetLocation = FVector::ZeroVector;
	if (UObject* Object = OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName))
	{
		APawn* Target = Cast<APawn>(Object);
		if (Target != nullptr)
		{
			TargetLocation = Target->GetActorLocation();
		}
	}
	else
	{
		TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BlackboardKey.SelectedKeyName);
	}

	float LookYaw = UKismetMathLibrary::FindLookAtRotation(ControllingPawn->GetActorLocation(), TargetLocation).Yaw;
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

	int32 Int_ControllingPawnYaw = static_cast<int32>(ControllingPawnRotator.Yaw);
	int32 Int_LookYaw = static_cast<int32>(LookYaw);
	int32 Int_Difference = FMath::Abs(Int_ControllingPawnYaw - Int_LookYaw);

	if (Int_Difference <= 1)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
