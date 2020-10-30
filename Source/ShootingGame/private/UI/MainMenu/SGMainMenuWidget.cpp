#include "SGMainMenuWidget.h"
#include "SGMainMenuPlayerController.h"
#include "SGSaveGame.h"
#include "SGGameInstance.h"
#include "Components/Button.h"

void USGMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SGMainMenuPlayerController = Cast<ASGMainMenuPlayerController>(GetOwningPlayer());
	SGGameInstance = Cast<USGGameInstance>(GetGameInstance());

	NewGameButton->OnClicked.AddDynamic(this, &USGMainMenuWidget::OnNewGameClicked);
	ExitButton->OnClicked.AddDynamic(this, &USGMainMenuWidget::OnExitClicked);
	
	SGSaveGame = SGGameInstance->GetSaveData();
	if (SGSaveGame != nullptr)
	{
		ContinueButton->OnClicked.AddDynamic(this, &USGMainMenuWidget::OnContinueClicked);
		ContinueButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ContinueButton->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void USGMainMenuWidget::OnNewGameClicked()
{
	SGMainMenuPlayerController->ShowSelectRifleWidget();
}

void USGMainMenuWidget::OnContinueClicked()
{
	SGCHECK(SGSaveGame);
	SGGameInstance->SetSelectedRifleName(SGSaveGame->RifleName);
	SGGameInstance->SetSelectedPistolName(SGSaveGame->PistolName);
	SGGameInstance->SetCurrentStage(SGSaveGame->Stage);
	SGGameInstance->LoadStage();
}

void USGMainMenuWidget::OnExitClicked()
{
	SGLOG(Warning, TEXT("Quit"));
	// 에디터까지 종료
	//FGenericPlatformMisc::RequestExit(true);
}
