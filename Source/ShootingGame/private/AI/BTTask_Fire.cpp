#include "BTTask_Fire.h"
#include "SGAICharacter.h"
#include "SGAICharacterAnimInstance.h"
#include "AIController.h"

UBTTask_Fire::UBTTask_Fire()
{
	bNotifyTick = true;
	bCreateNodeInstance = true;
	NodeName = TEXT("Fire");
}

EBTNodeResult::Type UBTTask_Fire::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type bResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	bDone = false;

	ASGAICharacter* AICharacter = Cast<ASGAICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (AICharacter == nullptr)
		return EBTNodeResult::Failed;

	USGAICharacterAnimInstance* AIAnimInstance = AICharacter->GetAnimInstance();
	if (AIAnimInstance == nullptr)
		return EBTNodeResult::Failed;

	float FireMontageLength = AIAnimInstance->PlayFireMontage(Count);

	GetWorld()->GetTimerManager().SetTimer(FireMontageTimerHandle, FTimerDelegate::CreateLambda([this, FireMontageLength]() -> void {
		bDone = true;
	}), FireMontageLength, false);

	return EBTNodeResult::InProgress;
}

void UBTTask_Fire::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (bDone)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
