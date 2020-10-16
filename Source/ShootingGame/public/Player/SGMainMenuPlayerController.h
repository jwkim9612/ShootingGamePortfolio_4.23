#pragma once

#include "ShootingGame.h"
#include "GameFramework/PlayerController.h"
#include "SGMainMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API ASGMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASGMainMenuPlayerController();

protected:
	virtual void BeginPlay() override;

private:
	void InitializeWidgets();

public:
	void ShowMainMenuWidget();
	void ShowSelectRifleWidget();
	void ShowSelectPistolWidget();
	void ShowWidget(class UUserWidget* Widget);

	class UUserWidget* GetCurrentWidget() const;

private:
	UPROPERTY(EditDefaultsOnly, category = "MainMenu")
	TSubclassOf<class USGMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, category = "MainMenu")
	TSubclassOf<class USGSelectRifleWidget> SelectRifleWidgetClass;

	UPROPERTY(EditDefaultsOnly, category = "MainMenu")
	TSubclassOf<class USGSelectPistolWidget> SelectPistolWidgetClass;

private:
	UPROPERTY()
	class USGMainMenuWidget* SGMainMenuWidget;

	UPROPERTY()
	class USGSelectRifleWidget* SGSelectRifleWidget;

	UPROPERTY()
	class USGSelectPistolWidget* SGSelectPistolWidget;

	UPROPERTY()
	class UUserWidget* CurrentWidget;
};
