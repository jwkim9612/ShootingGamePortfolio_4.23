#include "SGPlayerController.h"
#include "SGHUDWidget.h"
#include "SGHitEffect.h"
#include "SGFloatingDamageText.h"
#include "SGPlayerState.h"
#include "SGHPBar.h"
#include "SGCrossHair.h"

ASGPlayerController::ASGPlayerController()
{
	static ConstructorHelpers::FClassFinder<USGHUDWidget> SGHUDWidget_Class(TEXT("/Game/BluePrint/UI/InGame/BP_SGHUDWidget.BP_SGHUDWidget_C"));
	if (SGHUDWidget_Class.Succeeded())
	{
		SGHUDWidgetClass = SGHUDWidget_Class.Class;
	}
}

void ASGPlayerController::OnPossess(APawn * aPawn)
{
	Super::OnPossess(aPawn);

	SGPlayerState = Cast<ASGPlayerState>(PlayerState);
	SGCHECK(SGPlayerState);

	SGCHECK(SGHUDWidgetClass);
	SGHUDWidget = CreateWidget<USGHUDWidget>(this, SGHUDWidgetClass);
	SGHUDWidget->AddToViewport(0);
	SGHUDWidget->SetControllingPawn(aPawn);

	BindWidgetToPlayerState();
}

void ASGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly Mode;
	SetInputMode(Mode);

	SGHUDWidget->PlayFadeInScreenAnimation();
	SGHUDWidget->PlayFadeObjectiveAnimation();
}

USGHUDWidget * ASGPlayerController::GetSGHUDWidget() const
{
	return SGHUDWidget;
}

void ASGPlayerController::BindWidgetToPlayerState()
{
	SGPlayerState->OnHPChanged.AddLambda([this]() -> void
	{
		SGHUDWidget->GetSGHPBar()->SetHPProgressBar(SGPlayerState->GetHPRatio());
	});
}
