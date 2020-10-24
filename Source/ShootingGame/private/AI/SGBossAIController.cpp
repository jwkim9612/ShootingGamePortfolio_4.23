#include "SGBossAIController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

const FName ASGBossAIController::TargetKey(TEXT("Target"));

ASGBossAIController::ASGBossAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackboardDataObject(TEXT("BlackboardData'/Game/AI/Boss_Blackboard.Boss_Blackboard'"));
	if (BlackboardDataObject.Succeeded())
	{
		BlackBoardData = BlackboardDataObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObject(TEXT("BehaviorTree'/Game/AI/Boss_BehaviorTree.Boss_BehaviorTree'"));
	if (BehaviorTreeObject.Succeeded())
	{
		BehaviorTree = BehaviorTreeObject.Object;
	}
}

void ASGBossAIController::BeginPlay()
{
	Super::BeginPlay();

	if (UseBlackboard(BlackBoardData, Blackboard))
	{
		if (RunBehaviorTree(BehaviorTree))
		{
			SGLOG(Warning, TEXT("Run BehaviorTree"));
		}
	}
}
