#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGDiedWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGDiedWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	float PlayFadeAnimation();

private:
	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* Fade;
};
