#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGFloatingDamageText.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGFloatingDamageText : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetText(FString NewDamageText, bool bIsHitHead = false);
	void PlayFadeAnimation();

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DamageText;

	UPROPERTY(meta = (BindWidgetAnim))
	UWidgetAnimation* Fade;
};
