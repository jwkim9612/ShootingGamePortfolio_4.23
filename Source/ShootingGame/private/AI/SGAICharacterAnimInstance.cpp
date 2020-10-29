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
