#include "SGLevelScriptActorBase.h"
#include "SGGameInstance.h"
#include "SGPlayerController.h"
#include "SGHUDWidget.h"
#include "SGObjectiveHUD.h"

void ASGLevelScriptActorBase::BeginPlay()
{
	Super::BeginPlay();

	ObjectiveCount = 0;
	AttainmentCount = 0;

	SGGameInstance = Cast<USGGameInstance>(GetGameInstance());
	SGCHECK(SGGameInstance);
	SGGameInstance->CreateFloatingDamageTextPool();
	
	ASGPlayerController* SGPlayerController = Cast<ASGPlayerController>(SGGameInstance->GetPrimaryPlayerController());
	SGCHECK(SGPlayerController);

	SGObjectiveHUD = SGPlayerController->GetSGHUDWidget()->GetObjectiveHUD();
	SGCHECK(SGObjectiveHUD);
}

int32 ASGLevelScriptActorBase::GetObjectiveCount() const
{
	return ObjectiveCount;
}

int32 ASGLevelScriptActorBase::GetAttainmentCount() const
{
	return AttainmentCount;
}

bool ASGLevelScriptActorBase::IsQuestComplete() const
{
	return ObjectiveCount == AttainmentCount;
}

void ASGLevelScriptActorBase::AddAttainmentCount()
{
	AttainmentCount = FMath::Clamp(AttainmentCount + 1, 0, ObjectiveCount);
	SGObjectiveHUD->UpdateQuestText();

	if (IsQuestComplete())
	{
		OnQuestComplete.Broadcast();
	}
}
