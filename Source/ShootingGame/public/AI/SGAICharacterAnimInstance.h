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

public:
	float PlayFireMontage(int32 LoopCount);

private:
	UPROPERTY()
	class ASGAICharacter* AICharacter;

	UPROPERTY(EditAnywhere, Category = "Montage", meta = (AllowPrivateAccess = true))
	class UAnimMontage* FireMotage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	float CurrentSpeed;

private:
	int CurrentMontageLoopCount;
	float FireMontageTimer;
	FTimerHandle FireMontageTimerHandle;
};
