#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGWeaponHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGWeaponHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void UpdateAmmo();

	UFUNCTION()
	void UpdateWeapon();

	void SetCurrentWeapon(class ASGWeapon* NewWeapon);
	void BindPlayer(class ASGPlayer* NewPlayer);
	void BindWeapon(class ASGWeapon* NewWeapon);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Ammo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxAmmo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image;

private:
	UPROPERTY()
	class ASGWeapon* CurrentWeapon;
};
