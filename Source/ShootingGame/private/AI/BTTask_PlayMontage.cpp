#include "BTTask_PlayMontage.h"
#include "AIController.h"

UBTTask_PlayMontage::UBTTask_PlayMontage()
{
	bNotifyTick = true;
	bCreateNodeInstance = true;
	NodeName = TEXT("Fire");
}

EBTNodeResult::Type UBTTask_PlayMontage::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type bResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	bDone = false;

	ACharacter* Character = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	if (Character == nullptr)
		return EBTNodeResult::Failed;

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if (AnimInstance == nullptr)
		return EBTNodeResult::Failed;

	if (AnimMontage == nullptr)
		return EBTNodeResult::Failed;

	float MontageLength = AnimInstance->Montage_Play(AnimMontage);
	PlayCount = 0;
	GetWorld()->GetTimerManager().SetTimer(MontageTimerHandle, FTimerDelegate::CreateLambda([this, MontageLength, AnimInstance]() -> void {
		++PlayCount;
		if (PlayCount == Count)
		{
			bDone = true;
			GetWorld()->GetTimerManager().ClearTimer(MontageTimerHandle);
		}
		else
		{
			AnimInstance->Montage_Play(AnimMontage);
		}
	}), MontageLength, true);

	return EBTNodeResult::InProgress;
}

void UBTTask_PlayMontage::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (bDone)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
