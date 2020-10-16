#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "SGLoadingScreen.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGLoadingScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetData(struct FSGStageData* StageData);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StageName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StageDescription;

	UPROPERTY(meta = (BindWidget))
	class UImage* Background;

};
