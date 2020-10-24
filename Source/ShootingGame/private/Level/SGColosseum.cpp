#include "SGColosseum.h"
#include "SGBoss.h"
#include "EngineUtils.h"
#include "SGObjectiveHUD.h"

void ASGColosseum::BeginPlay()
{
	Super::BeginPlay();

	for (const auto& Boss : TActorRange<ASGBoss>(GetWorld()))
	{
		Boss->OnDead.AddDynamic(this, &ASGColosseum::AddAttainmentCount);
		++ObjectiveCount;
	}

	SGObjectiveHUD->UpdateQuestText();
}
