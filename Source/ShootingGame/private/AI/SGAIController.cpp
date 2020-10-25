#include "SGAIController.h"
#include "SGAICharacter.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

const FName ASGAIController::bDetectedKey = TEXT("bDetected");
const FName ASGAIController::OriginLocationKey = TEXT("OriginLocation");
const FName ASGAIController::PatrolLocationKey = TEXT("PatrolLocation");

ASGAIController::ASGAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackboardDataObject(TEXT("BlackboardData'/Game/AI/AI_BlackboardData.AI_BlackboardData'"));
	if (BlackboardDataObject.Succeeded())
	{
		BlackBoardData = BlackboardDataObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObject(TEXT("BehaviorTree'/Game/AI/AI_BehaviorTree.AI_BehaviorTree'"));
	if (BehaviorTreeObject.Succeeded())
	{
		BehaviorTree = BehaviorTreeObject.Object;
	}
	
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent")));
	AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISightConfig"));
	AISightConfig->SightRadius = 500.0f;
	AISightConfig->LoseSightRadius = 500.0f;
	PerceptionComponent->ConfigureSense(*AISightConfig);

	SetGenericTeamId(FGenericTeamId(1));
}

void ASGAIController::BeginPlay()
{
	Super::BeginPlay();

	SGAICharacter = Cast<ASGAICharacter>(GetPawn());
	SGCHECK(SGAICharacter);

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ASGAIController::OnTargetPerceptionUpdated);

	if (UseBlackboard(BlackBoardData, Blackboard))
	{
		if (RunBehaviorTree(BehaviorTree))
		{
			Blackboard->SetValueAsVector(OriginLocationKey, SGAICharacter->GetActorLocation());
			Blackboard->SetValueAsVector(PatrolLocationKey, SGAICharacter->GetActorLocation() + SGAICharacter->GetActorForwardVector() * 500.0f);
		}
	}
}

void ASGAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	bool bOnTarget = Stimulus.WasSuccessfullySensed();
	Blackboard->SetValueAsBool(bDetectedKey, bOnTarget);
}
