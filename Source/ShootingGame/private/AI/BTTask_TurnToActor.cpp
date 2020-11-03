#include "BTTask_TurnToActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "SGAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToActor::UBTTask_TurnToActor()
{
	bNotifyTick = true;
	bCreateNodeInstance = true;
	NodeName = TEXT("TurnToActor");
}

EBTNodeResult::Type UBTTask_TurnToActor::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;

	Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	if (Target == nullptr)
		return EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}

void UBTTask_TurnToActor::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	Turn();
	
	if (IsDone())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_TurnToActor::Turn()
{
	SGCHECK(Target);

	FVector ControllingPawnLocation = ControllingPawn->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();

	float LookAtYaw = UKismetMathLibrary::FindLookAtRotation(ControllingPawnLocation, TargetLocation).Yaw;
	float ControllingPawnYaw = ControllingPawn->GetActorRotation().Yaw;

	float LookAtYawConverted360 = Get180DegreeTo360Degree(LookAtYaw);
	float PawnYawConverted360 = Get180DegreeTo360Degree(ControllingPawnYaw);

	float ResultValue = PawnYawConverted360 - LookAtYawConverted360;
	if (ResultValue > 0.0f)
	{
		if (ResultValue >= 180.0f)
		{
			ControllingPawn->AddActorWorldRotation(FRotator(0.0f, 2.0f, 0.0f));
		}
		else
		{
			ControllingPawn->AddActorWorldRotation(FRotator(0.0f, -2.0f, 0.0f));
		}
	}
	else if (ResultValue < 0.0f)
	{
		if (ResultValue <= -180.0f)
		{
			ControllingPawn->AddActorWorldRotation(FRotator(0.0f, -2.0f, 0.0f));
		}
		else
		{
			ControllingPawn->AddActorWorldRotation(FRotator(0.0f, 2.0f, 0.0f));
		}
	}
}

bool UBTTask_TurnToActor::IsDone()
{
	FVector ControllingPawnLocation = ControllingPawn->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();

	float LookAtYaw = UKismetMathLibrary::FindLookAtRotation(ControllingPawnLocation, TargetLocation).Yaw;
	float ControllingPawnYaw = ControllingPawn->GetActorRotation().Yaw;

	int32 Int_ControllingPawnYaw = static_cast<int32>(ControllingPawnYaw);
	int32 Int_LookYaw = static_cast<int32>(LookAtYaw);
	int32 Int_Difference = FMath::Abs(Int_ControllingPawnYaw) - FMath::Abs(Int_LookYaw);

	if (Int_Difference <= 1)
		return true;
	
	return false;
}

float UBTTask_TurnToActor::Get180DegreeTo360Degree(float ValueToConvert)
{
	float ConvertedValue = 0.0f;
	if (ValueToConvert < 0)
	{
		ConvertedValue = 360.0f + ValueToConvert;
	}
	else
	{
		ConvertedValue = ValueToConvert;
	}

	return ConvertedValue;
}
