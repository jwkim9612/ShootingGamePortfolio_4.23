#include "AnimNotify_Fire.h"
#include "SGAICharacterBase.h"
#include "SGPlayer.h"

void UAnimNotify_Fire::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ASGAICharacterBase* ControllingAICharacter = Cast<ASGAICharacterBase>(MeshComp->GetOwner());
	SGCHECK(ControllingAICharacter);

	AActor* Target = ControllingAICharacter->GetTarget();
	if (Target != nullptr)
	{
		FVector TargetLocation = Target->GetActorLocation();
		ControllingAICharacter->Fire(TargetLocation);
	}
}
