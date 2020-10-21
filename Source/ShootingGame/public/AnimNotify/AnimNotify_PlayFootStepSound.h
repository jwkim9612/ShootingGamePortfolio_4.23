#pragma once

#include "ShootingGame.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_PlayFootStepSound.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Play FootStep Sound"))
class SHOOTINGGAME_API UAnimNotify_PlayFootStepSound : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "AnimNotify")
	TSubclassOf<class USGFootStepSoundList> SoundListClass;

	UPROPERTY()
	class USGFootStepSoundList* SoundList;

	UPROPERTY(EditAnywhere, Category = "AnimNotify")
	FName SocketName;
};
