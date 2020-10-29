#pragma once

#include "ShootingGame.h"
#include "Animation/AnimInstance.h"
#include "SGAICharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGAICharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY()
	class ASGAICharacter* AICharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	float CurrentSpeed;
};
