#include "SGLoadingScreen.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USGLoadingScreen::SetData(struct FSGStageData* StageData)
{
	StageName->SetText(FText::FromString(StageData->Name));
	StageDescription->SetText(FText::FromString(StageData->Description));
	Background->SetBrushFromTexture(StageData->Image);
}
