#include "SGMainMenuGameMode.h"

ASGMainMenuGameMode::ASGMainMenuGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerController> MainMenuPlayerController_Class(TEXT("/Game/BluePrint/Player/BP_SGMainMenuPlayerController.BP_SGMainMenuPlayerController_C"));
	if (MainMenuPlayerController_Class.Succeeded())
	{
		PlayerControllerClass = MainMenuPlayerController_Class.Class;
	}
}
