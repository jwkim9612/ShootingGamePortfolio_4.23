#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGWeaponButton.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGWeaponButton : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void SetWeaponData(FSGWeaponData* WeaponData);
	void SetWeaponType(WeaponType NewType);

private:
	UFUNCTION()
	void OnClicked();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ChooseButton;

	UPROPERTY(meta = (BindWidget))
	class UImage* WeaponImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DamageText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxAmmoText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ClipSizeText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FireRateText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RecoliText;

	WeaponType Type;
};
