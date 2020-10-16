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
	else
	{
		SGLOG(Warning, TEXT("HUDWidgetClass is null!!"));
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
}

USGHUDWidget * ASGPlayerController::GetSGHUDWidget() const
{
	return SGHUDWidget;
}

void ASGPlayerController::SetDefaultSpreadCrossHair(float SpreadValue)
{
	auto CrossHair = SGHUDWidget->GetSGCrossHair();
	SGCHECK(CrossHair);
	CrossHair->SetDefaultSpreadValue(SpreadValue);
}

void ASGPlayerController::SetCurrentSpreadCrossHair(float SpreadValue)
{
	auto CrossHair = SGHUDWidget->GetSGCrossHair();
	SGCHECK(CrossHair);
	CrossHair->SetCurrentSpreadValue(SpreadValue);
}

void ASGPlayerController::BindWidgetToPlayerState()
{
	SGPlayerState->OnHPChanged.AddLambda([this]() -> void
	{
		SGHUDWidget->GetSGHPBar()->SetHPProgressBar(SGPlayerState->GetHPRatio());
	});
}
