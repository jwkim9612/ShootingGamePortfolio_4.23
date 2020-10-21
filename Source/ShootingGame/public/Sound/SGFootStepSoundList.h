#pragma once

#include "ShootingGame.h"
#include "UObject/NoExportTypes.h"
#include "SGFootStepSoundList.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SHOOTINGGAME_API USGFootStepSoundList : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Sound", Meta = (AllowPrivateAccess = true))
	TMap<FString, class USoundCue*> SoundList;

public:
	class USoundCue* GetSound(FString SoundName);
};
