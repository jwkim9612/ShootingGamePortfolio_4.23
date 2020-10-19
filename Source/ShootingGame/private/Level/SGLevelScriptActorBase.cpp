#include "SGLevelScriptActorBase.h"
#include "SGGameInstance.h"

void ASGLevelScriptActorBase::BeginPlay()
{
	Super::BeginPlay();

	SGGameInstance = Cast<USGGameInstance>(GetGameInstance());
	SGGameInstance->CreateFloatingDamageTextPool();
}
