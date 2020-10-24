#pragma once

#include "ShootingGame.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Fire.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Fire"))
class SHOOTINGGAME_API UAnimNotify_Fire : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override; 

private:
	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (AllowPrivateAccess = true))
	int32 Count;


};
