#pragma once

#include "ShootingGame.h"
#include "UI/MainMenu/SGSelectWeaponWidget.h"
#include "SGSelectPistolWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGSelectPistolWidget : public USGSelectWeaponWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

protected:
	virtual void UpdateWeaponButtons() override;

private:
	virtual void OnSelectClicked() override;
	virtual void OnBackClicked() override;
};
