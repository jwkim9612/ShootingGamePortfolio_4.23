#include "SGMainMenuWidget.h"
#include "SGMainMenuPlayerController.h"
#include "SGSaveGame.h"
#include "SGGameInstance.h"
#include "Components/Button.h"

void USGMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SGMainMenuPlayerController = Cast<ASGMainMenuPlayerController>(GetOwningPlayer());

	NewGameButton->OnClicked.AddDynamic(this, &USGMainMenuWidget::OnNewGameClicked);
	ExitButton->OnClicked.AddDynamic(this, &USGMainMenuWidget::OnExitClicked);
	
	if (HasSaveData())
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
	USGGameInstance* SGGameInstance = Cast<USGGameInstance>(GetGameInstance());
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

bool USGMainMenuWidget::HasSaveData()
{
	SGSaveGame = Cast<USGSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerSaveData"), 0));
	if(SGSaveGame != nullptr)
	{
		return true;
	}

	return false;
}
