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
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerPawnBPClass is null!"));
	}

	static ConstructorHelpers::FClassFinder<APlayerController> SGPlayerControllerClass(TEXT("/Game/BluePrint/Player/BP_SGPlayerController.BP_SGPlayerController_C"));
	if (SGPlayerControllerClass.Succeeded())
	{
		PlayerControllerClass = SGPlayerControllerClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerContoller is null!"));
	}

	static ConstructorHelpers::FClassFinder<APlayerState> SGPlayerStateClass(TEXT("/Game/BluePrint/Player/BP_SGPlayerState.BP_SGPlayerState_C"));
	if (SGPlayerStateClass.Succeeded())
	{
		PlayerStateClass = SGPlayerStateClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerState is null!"));
	}
}
