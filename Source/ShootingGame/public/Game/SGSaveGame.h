#pragma once

#include "ShootingGame.h"
#include "GameFramework/SaveGame.h"
#include "SGSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	USGSaveGame();

public:
	UPROPERTY()
	FString RifleName;

	UPROPERTY()
	FString PistolName;

	UPROPERTY()
	int32 RifleMaxAmmo;

	UPROPERTY()
	int32 RifleAmmo;

	UPROPERTY()
	int32 PistolMaxAmmo;

	UPROPERTY()
	int32 PistolAmmo;

	UPROPERTY()
	int32 Stage;
};
