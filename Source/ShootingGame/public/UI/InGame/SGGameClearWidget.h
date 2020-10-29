#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGGameClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGGameClearWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	float PlayFadeAnimation();

private:
	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* Fade;
};
