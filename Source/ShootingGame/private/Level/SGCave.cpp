﻿#include "SGCave.h"
#include "SGKey.h"
#include "EngineUtils.h"
#include "SGObjectiveHUD.h"

void ASGCave::BeginPlay()
{
	Super::BeginPlay();

	for (const auto& Key : TActorRange<ASGKey>(GetWorld()))
	{
		Key->OnPickup.AddUFunction(this, TEXT("AddAttainmentCount"));
		++ObjectiveCount;
	}
	
	SGObjectiveHUD->UpdateQuestText();
}
