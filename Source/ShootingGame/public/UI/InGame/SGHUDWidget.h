#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

public:
	void PlayFadeInHPBarAnimation();
	void PlayFadeOutHPBarAnimation();
	void PlayFadeInBossHPBarAnimation();
	void PlayFadeOutBossHPBarAnimation();
	void PlayFadeHitEffectAnimation();
	void PlayFadeObjectiveAnimation();
	void PlayFadeInScreenAnimation();
	float PlayFadeOutScreenAnimation();
	float PlayFadeDiedAnimation();

	void SetControllingPawn(APawn* aPawn);

	class USGHPBar* GetSGHPBar() const;
	class USGHPBar* GetSGBossHPBar() const;
	class USGCrossHair* GetSGCrossHair() const;
	class USGWeaponHUD* GetWeaponHUD() const;
	class USGObjectiveHUD* GetObjectiveHUD() const;

private:
	UPROPERTY(meta = (BindWidget))
	class USGHPBar* SGHPBar;

	UPROPERTY(meta = (BindWidget))
	class USGHPBar* SGBossHPBar;

	UPROPERTY(meta = (BindWidget))
	class USGCrossHair* SGCrossHair;

	UPROPERTY(meta = (BindWidget))
	class USGHitEffect* SGHitEffect;

	UPROPERTY(meta = (BindWidget))
	class USGWeaponHUD* SGWeaponHUD;

	UPROPERTY(meta = (BindWidget))
	class USGObjectiveHUD* SGObjectiveHUD;

	UPROPERTY(meta = (BindWidget))
	class USGDiedWidget* SGDiedWidget;

	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeInHPBar;

	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeOutHPBar;

	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeInBossHPBar;

	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeOutBossHPBar;

	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeInScreen;

	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeOutScreen;

private:
	UPROPERTY()
	class ASGPlayer* SGPlayer;

private:
	bool bIsOnShowHPBar;
};
