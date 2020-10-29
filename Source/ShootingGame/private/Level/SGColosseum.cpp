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
		Boss->OnDead.AddDynamic(this, &ASGColosseum::PlayGameClearAnimation);
		++ObjectiveCount;
	}

	SGObjectiveHUD->UpdateQuestText();
	SetFadeInBossHPBarAnimationTimer();
}

void ASGColosseum::SetFadeInBossHPBarAnimationTimer()
{
	float ObjectiveAnimationLength = SGObjectiveHUD->GetFadeAnimationLength();
	if (SGPlayerController != nullptr)
	{
		GetWorld()->GetTimerManager().SetTimer(FadeInBossHPBarTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
			SGPlayerController->GetSGHUDWidget()->PlayFadeInBossHPBarAnimation();
		}), ObjectiveAnimationLength, false);
	}
}

void ASGColosseum::PlayGameClearAnimation()
{
	SGLOG(Warning, TEXT("Clear Animation"));
	float GameClearAnimationLength = SGPlayerController->GetSGHUDWidget()->PlayFadeGameClearAnimation();
	if (SGPlayerController != nullptr)
	{
		GetWorld()->GetTimerManager().SetTimer(FadeInBossHPBarTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
			SGGameInstance->LoadMainMenu();
		}), GameClearAnimationLength, false);
	}
}
