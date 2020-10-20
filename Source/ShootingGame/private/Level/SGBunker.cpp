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

	SGObjectiveHUD->UpdateQuestText();
}
