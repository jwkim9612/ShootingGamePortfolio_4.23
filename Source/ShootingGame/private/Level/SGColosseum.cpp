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
		Boss->OnDead.AddUFunction(this, TEXT("AddAttainmentCount"));
		Boss->OnDead.AddUFunction(this, TEXT("PlayGameClearAnimation"));
		Boss->OnDead.AddUFunction(this, TEXT("DeleteSaveData"));
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
	float GameClearAnimationLength = SGPlayerController->GetSGHUDWidget()->PlayFadeGameClearAnimation();
	if (SGPlayerController != nullptr)
	{
		GetWorld()->GetTimerManager().SetTimer(FadeInBossHPBarTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
			SGGameInstance->LoadMainMenu();
		}), GameClearAnimationLength, false);
	}
}

void ASGColosseum::DeleteSaveData()
{
	SGCHECK(SGGameInstance);
	SGGameInstance->DeleteSaveData();
}
