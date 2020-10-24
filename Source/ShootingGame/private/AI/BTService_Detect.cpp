#include "BTService_Detect.h"
#include "SGBossAIController.h"
#include "SGAICharacterBase.h"
#include "SGPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ASGAICharacterBase* ControllingAICharacter = Cast<ASGAICharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	SGCHECK(ControllingAICharacter);

	UWorld* World = ControllingAICharacter->GetWorld();
	SGCHECK(World);

	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingAICharacter);
	FVector Center = ControllingAICharacter->GetActorLocation();
	TArray<FOverlapResult> OverlapResults;
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	//DrawDebugSphere(World, Center, DetectRadius, 50, FColor::Yellow, false, 10.0f);

	if (bResult)
	{
		for (const auto& OverlapResult : OverlapResults)
		{
			ASGPlayer* SGPlayer = Cast<ASGPlayer>(OverlapResult.GetActor());
			ControllingAICharacter->SetTarget(SGPlayer);
			if (SGPlayer != nullptr)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASGBossAIController::TargetKey, SGPlayer);
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASGBossAIController::TargetKey, nullptr);
	}
}
