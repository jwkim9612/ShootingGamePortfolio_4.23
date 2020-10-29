#include "SGObjectiveHUD.h"
#include "SGGameInstance.h"
#include "SGLevelScriptActorBase.h"
#include "Components/TextBlock.h"

void USGObjectiveHUD::NativeConstruct()
{
	Super::NativeConstruct();

	SGGameInstance = Cast<USGGameInstance>(GetGameInstance());
	SGLevelScriptActor = Cast<ASGLevelScriptActorBase>(GetWorld()->GetLevelScriptActor());
	SGLevelScriptActor->OnQuestComplete.AddDynamic(this, &USGObjectiveHUD::PlayFadeOpenedPortalAnimation);
	SGLevelScriptActor->OnQuestComplete.AddDynamic(this, &USGObjectiveHUD::SetQuestTextColorForComplete);
}

void USGObjectiveHUD::PlayFadeAnimation()
{
	SGCHECK(Fade);
	PlayAnimation(Fade);
}

float USGObjectiveHUD::GetFadeAnimationLength()
{
	return Fade->GetEndTime();
}

void USGObjectiveHUD::PlayFadeOpenedPortalAnimation()
{
	SGCHECK(FadeOpenedPortal);
	PlayAnimation(FadeOpenedPortal);
}

void USGObjectiveHUD::SetQuestTextColorForComplete()
{
	QuestText->SetColorAndOpacity(FLinearColor::Yellow);
}

void USGObjectiveHUD::UpdateTitleAndObjetiveText()
{
	SGCHECK(SGGameInstance);
	FSGStageData* StageData = SGGameInstance->TryGetStageData(SGGameInstance->GetCurrentStage());
	SGCHECK(StageData);
	
	TitleText->SetText(FText::FromString(StageData->Name));
	ObjectiveText->SetText(FText::FromString(StageData->Objective));
}

void USGObjectiveHUD::SetQuestText(FString& NewQuestString)
{
	QuestString = NewQuestString;
}

void USGObjectiveHUD::UpdateQuestText()
{
	int32 AttainmentCount = SGLevelScriptActor->GetAttainmentCount();
	int32 ObjectiveCount = SGLevelScriptActor->GetObjectiveCount();

	QuestText->SetText(FText::FromString(FString::Printf(TEXT("● %s : %d / %d"), *QuestString, AttainmentCount, ObjectiveCount)));
}
