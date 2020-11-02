#include "SGGameMode.h"
#include "SGPlayer.h"
#include "SGPlayerController.h"
#include "SGPlayerState.h"

ASGGameMode::ASGGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> SGPlayerPawnBPClass(TEXT("/Game/BluePrint/Player/BP_SGPlayer"));
	if (SGPlayerPawnBPClass.Succeeded())
	{
		DefaultPawnClass = SGPlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> SGPlayerControllerClass(TEXT("/Game/BluePrint/Player/BP_SGPlayerController.BP_SGPlayerController_C"));
	if (SGPlayerControllerClass.Succeeded())
	{
		PlayerControllerClass = SGPlayerControllerClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerState> SGPlayerStateClass(TEXT("/Game/BluePrint/Player/BP_SGPlayerState.BP_SGPlayerState_C"));
	if (SGPlayerStateClass.Succeeded())
	{
		PlayerStateClass = SGPlayerStateClass.Class;
	}
}
