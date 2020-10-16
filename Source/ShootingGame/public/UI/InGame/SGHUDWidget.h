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
	void PlayFadeHitEffectAnimation();
	void PlayFadeInScreenAnimation();
	float PlayFadeOutScreenAnimation();

	void SetControllingPawn(APawn* aPawn);

	class USGHPBar* GetSGHPBar() const;
	class USGCrossHair* GetSGCrossHair() const;
	class USGWeaponHUD* GetWeaponHUD() const;

private:
	UPROPERTY(meta = (BindWidget))
	class USGHPBar* SGHPBar;

	UPROPERTY(meta = (BindWidget))
	class USGCrossHair* SGCrossHair;

	UPROPERTY(meta = (BindWidget))
	class USGHitEffect* SGHitEffect;

	UPROPERTY(meta = (BindWidget))
	class USGWeaponHUD* SGWeaponHUD;

	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeInHPBar;

	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeOutHPBar;

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
