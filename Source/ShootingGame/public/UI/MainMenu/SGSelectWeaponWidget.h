#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGSelectWeaponWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGSelectWeaponWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void ShowSelectButton();
	void HideSelectButton();
	void SetSelectedWeaponText(FString WeaponName);
	void ShowSelectedWeaponText();
	void HideSelectedWeaponText();

protected:
	UFUNCTION()
	virtual void OnSelectClicked();

	UFUNCTION()
	virtual void OnBackClicked();

	UFUNCTION()
	void OnNextClicked();

	UFUNCTION()
	void OnPreviousClicked();

	virtual void UpdateWeaponButtons();

private:
	void CreateWeaponButtonList();
	void UpdatePageButtonsVisibility();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* SelectButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* NextButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* PreviousButton;

	UPROPERTY(meta = (BindWidget))
	class USGWeaponButton* SGWeaponButton;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* WeaponButtonBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SelectedWeaponText;

	UPROPERTY()
	class ASGMainMenuPlayerController* SGMainMenuPlayerController;

	UPROPERTY()
	class USGGameInstance* SGGameInstance;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	TArray<FString> WeaponNameList;

	UPROPERTY()
	TArray<class USGWeaponButton*> WeaponButtonList;

	int32 CurrentPage;
	int32 PageCount;
};
