#include "SGCity.h"
#include "EngineUtils.h"
#include "SGStar.h"
#include "SGObjectiveHUD.h"

void ASGCity::BeginPlay()
{
	Super::BeginPlay();

	for (const auto& Star : TActorRange<ASGStar>(GetWorld()))
	{
		Star->OnPickup.AddUFunction(this, TEXT("AddAttainmentCount"));
		++ObjectiveCount;
	}

	SGObjectiveHUD->UpdateQuestText();
}
