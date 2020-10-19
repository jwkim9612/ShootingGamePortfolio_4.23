#include "SGObjectiveHUD.h"
#include "SGGameInstance.h"
#include "Components/TextBlock.h"

void USGObjectiveHUD::NativeConstruct()
{
	Super::NativeConstruct();

	SGGameInstance = Cast<USGGameInstance>(GetGameInstance());
}

void USGObjectiveHUD::PlayFadeAnimation()
{
	SGCHECK(Fade);
	PlayAnimation(Fade);
}

void USGObjectiveHUD::UpdateText()
{
	SGCHECK(SGGameInstance);
	FSGStageData* StageData = SGGameInstance->TryGetStageData(SGGameInstance->GetCurrentStage());
	SGCHECK(StageData);
	
	TitleText->SetText(FText::FromString(StageData->Name));
	ObjectiveText->SetText(FText::FromString(StageData->Objective));
}
