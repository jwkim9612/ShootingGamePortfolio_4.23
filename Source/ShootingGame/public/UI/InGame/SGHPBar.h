#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGHPBar.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGHPBar : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetHPProgressBar(float HPRatio);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPProgressBar;
};
