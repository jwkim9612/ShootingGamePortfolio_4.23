#include "AnimNotify_Fire.h"
#include "SGAICharacterBase.h"
#include "SGPlayer.h"
#include "Kismet/KismetMathLibrary.h"

void UAnimNotify_Fire::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ASGAICharacterBase* ControllingAICharacter = Cast<ASGAICharacterBase>(MeshComp->GetOwner());
	SGCHECK(ControllingAICharacter);

	ASGPlayer* Target = ControllingAICharacter->GetTarget();
	if (Target != nullptr)
	{
		FVector MuzzleLocation = ControllingAICharacter->GetMesh()->GetSocketLocation("Muzzle");
		FVector TargetLocation = Target->GetActorLocation();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(MuzzleLocation, TargetLocation);
		ControllingAICharacter->Fire(LookAtRotation.Vector());
	}
}
