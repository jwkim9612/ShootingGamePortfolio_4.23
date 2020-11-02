#include "BTTask_TurnToLocation.h"
#include "Kismet/KismetMathLibrary.h"
#include "SGAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToLocation::UBTTask_TurnToLocation()
{
	bNotifyTick = true;
	bCreateNodeInstance = true;
	NodeName = TEXT("TurnToLocation");
}

EBTNodeResult::Type UBTTask_TurnToLocation::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;

	TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BlackboardKey.SelectedKeyName);

	return EBTNodeResult::InProgress;
}

void UBTTask_TurnToLocation::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	Turn(DeltaSeconds);

	if (IsDone())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_TurnToLocation::Turn(float DeltaSeconds)
{
	float LookAtYaw = UKismetMathLibrary::FindLookAtRotation(ControllingPawn->GetActorLocation(), TargetLocation).Yaw;
	FRotator ControllingPawnRotator = ControllingPawn->GetActorRotation();

	ControllingPawn->SetActorRelativeRotation(
		FRotator(
			ControllingPawnRotator.Pitch,
			FMath::FInterpTo(
				ControllingPawnRotator.Yaw,
				LookAtYaw, DeltaSeconds,
				TurnSpeed),
			ControllingPawnRotator.Roll)
	);
}

bool UBTTask_TurnToLocation::IsDone()
{
	float LookAtYaw = UKismetMathLibrary::FindLookAtRotation(ControllingPawn->GetActorLocation(), TargetLocation).Yaw;
	FRotator ControllingPawnRotator = ControllingPawn->GetActorRotation();

	int32 Int_ControllingPawnYaw = static_cast<int32>(ControllingPawnRotator.Yaw);
	int32 Int_LookYaw = static_cast<int32>(LookAtYaw);
	int32 Int_Difference = FMath::Abs(Int_ControllingPawnYaw - Int_LookYaw);

	if (Int_Difference == 0)
		return true;

	return false;
}

