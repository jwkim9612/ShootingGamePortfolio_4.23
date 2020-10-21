#include "SGCity.h"
#include "EngineUtils.h"
#include "SGStar.h"
#include "SGObjectiveHUD.h"

void ASGCity::BeginPlay()
{
	Super::BeginPlay();

	for (const auto& Star : TActorRange<ASGStar>(GetWorld()))
	{
		Star->OnPickup.AddDynamic(this, &ASGCity::AddAttainmentCount);
		++ObjectiveCount;
	}

	SGObjectiveHUD->UpdateQuestText();
}
