#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGMainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnNewGameClicked();

	UFUNCTION()
	void OnContinueClicked();

	UFUNCTION()
	void OnExitClicked();

private:
	void SetContinueButton();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* NewGameButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ContinueButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;

private:
	UPROPERTY()
	class USGGameInstance* SGGameInstance;

	UPROPERTY()
	class ASGMainMenuPlayerController* SGMainMenuPlayerController;

	UPROPERTY()
	class USGSaveGame* SGSaveGame;
};
