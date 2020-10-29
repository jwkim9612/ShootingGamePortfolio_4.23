#include "SGHUDWidget.h"
#include "SGHPBar.h"
#include "SGCrossHair.h"
#include "SGWeaponHUD.h"
#include "SGHitEffect.h"
#include "SGObjectiveHUD.h"
#include "SGPlayer.h"
#include "SGDiedWidget.h"

bool USGHUDWidget::Initialize()
{
	bool bResult = Super::Initialize();

	bIsOnShowHPBar = false;

	return bResult;
}

void USGHUDWidget::PlayFadeInHPBarAnimation()
{
	if (!bIsOnShowHPBar)
	{
		PlayAnimation(FadeInHPBar);
	}

	bIsOnShowHPBar = true;
}

void USGHUDWidget::PlayFadeOutHPBarAnimation()
{
	if (bIsOnShowHPBar)
	{
		PlayAnimation(FadeOutHPBar);
	}

	bIsOnShowHPBar = false;
}

void USGHUDWidget::PlayFadeInBossHPBarAnimation()
{
	PlayAnimation(FadeInBossHPBar);
}

void USGHUDWidget::PlayFadeOutBossHPBarAnimation()
{
	PlayAnimation(FadeOutBossHPBar);
}

void USGHUDWidget::PlayFadeHitEffectAnimation()
{
	SGCHECK(SGHitEffect);
	SGHitEffect->PlayFadeAnimation();
}

void USGHUDWidget::PlayFadeObjectiveAnimation()
{
	SGCHECK(SGObjectiveHUD);
	SGObjectiveHUD->UpdateTitleAndObjetiveText();
	SGObjectiveHUD->PlayFadeAnimation();
}

void USGHUDWidget::PlayFadeInScreenAnimation()
{
	SGCHECK(FadeInScreen);
	PlayAnimation(FadeInScreen);
}

float USGHUDWidget::PlayFadeOutScreenAnimation()
{
	PlayAnimation(FadeOutScreen);
	return FadeOutScreen->GetEndTime();
}

float USGHUDWidget::PlayFadeDiedAnimation()
{
	SGCrossHair->SetRenderOpacity(0.0f);
	SGWeaponHUD->SetRenderOpacity(0.0f);
	SGObjectiveHUD->SetRenderOpacity(0.0f);
	SGHPBar->SetRenderOpacity(0.0f);
	SGBossHPBar->SetRenderOpacity(0.0f);

	float AnimationLength = SGDiedWidget->PlayFadeAnimation();
	return AnimationLength;
}

void USGHUDWidget::SetControllingPawn(APawn * aPawn)
{
	SGPlayer = Cast<ASGPlayer>(aPawn);
	SGCHECK(SGPlayer);

	SGWeaponHUD->BindPlayer(SGPlayer);
}

USGHPBar* USGHUDWidget::GetSGHPBar() const
{
	return SGHPBar;
}

USGHPBar * USGHUDWidget::GetSGBossHPBar() const
{
	return SGBossHPBar;
}

USGCrossHair * USGHUDWidget::GetSGCrossHair() const
{
	return SGCrossHair;
}

USGWeaponHUD * USGHUDWidget::GetWeaponHUD() const
{
	return SGWeaponHUD;
}

USGObjectiveHUD * USGHUDWidget::GetObjectiveHUD() const
{
	return SGObjectiveHUD;
}
