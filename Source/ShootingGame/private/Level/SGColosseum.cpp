#include "SGColosseum.h"
#include "SGBoss.h"
#include "SGPlayerController.h"
#include "SGHUDWidget.h"
#include "SGHPBar.h"
#include "SGGameInstance.h"
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
	SetFadeInBossHPBarAnimationTimer();
}

void ASGColosseum::SetFadeInBossHPBarAnimationTimer()
{
	float ObjectiveAnimationLength = SGObjectiveHUD->GetFadeAnimationLength();
	ASGPlayerController* SGPlayerController = Cast<ASGPlayerController>(SGGameInstance->GetPrimaryPlayerController());
	if (SGPlayerController != nullptr)
	{
		GetWorld()->GetTimerManager().SetTimer(FadeInBossHPBarTimerHandle, FTimerDelegate::CreateLambda([this, SGPlayerController]() -> void {
			SGPlayerController->GetSGHUDWidget()->PlayFadeInBossHPBarAnimation();
		}), ObjectiveAnimationLength, false);
	}
}
