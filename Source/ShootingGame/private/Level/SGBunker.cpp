#include "SGBunker.h"
#include "SGAICharacter.h"
#include "SGObjectiveHUD.h"
#include "EngineUtils.h"

void ASGBunker::BeginPlay()
{
	Super::BeginPlay();
	
	for (const auto& AICharacter : TActorRange<ASGAICharacter>(GetWorld()))
	{
		AICharacter->OnDead.AddDynamic(this, &ASGBunker::AddAttainmentCount);
		++ObjectiveCount;
	}

	FString Quest = TEXT("처치한 적의 수");
	SGObjectiveHUD->SetQuestText(Quest);
	SGObjectiveHUD->UpdateQuestText();
}
