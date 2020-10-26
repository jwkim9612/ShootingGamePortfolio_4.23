#include "SGAICharacterAnimInstance.h"
#include "SGAICharacter.h"

void USGAICharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	AICharacter = Cast<ASGAICharacter>(TryGetPawnOwner());
	SGCHECK(AICharacter);
}

void USGAICharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (AICharacter != nullptr)
	{
		CurrentSpeed = AICharacter->GetVelocity().Size();
	}
}

float USGAICharacterAnimInstance::PlayFireMontage(int32 LoopCount)
{
	if (LoopCount == 0 || FireMotage == nullptr)
		return 0.0f;

	CurrentMontageLoopCount = 1;

	FireMontageTimer = Montage_Play(FireMotage);

	GetWorld()->GetTimerManager().SetTimer(FireMontageTimerHandle, FTimerDelegate::CreateLambda([this, LoopCount]() -> void {
		if (CurrentMontageLoopCount == LoopCount)
		{
			GetWorld()->GetTimerManager().ClearTimer(FireMontageTimerHandle);
		}
		else
		{
			Montage_Play(FireMotage);
			++CurrentMontageLoopCount;
		}
	}), FireMontageTimer, true);

	return FireMontageTimer * LoopCount;
}
