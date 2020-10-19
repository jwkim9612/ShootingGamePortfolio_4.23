#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGObjectiveHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGObjectiveHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
public:
	void PlayFadeAnimation();
	void UpdateText();

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TitleText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ObjectiveText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* QuestText;

	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* Fade;

private:
	UPROPERTY()
	class USGGameInstance* SGGameInstance;
};