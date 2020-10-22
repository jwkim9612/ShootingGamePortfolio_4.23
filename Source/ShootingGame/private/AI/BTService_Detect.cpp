#include "BTService_Detect.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AActor* ControllingActor = OwnerComp.GetOwner();
	SGCHECK(ControllingActor);

	UWorld* World = ControllingActor->GetWorld();
	SGCHECK(World);

	TArray<FOverlapResult> OverlapResults;
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		ControllingActor->GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius)
	);

	if (bResult)
	{
		SGLOG(Warning, TEXT("True"));
	}
}
