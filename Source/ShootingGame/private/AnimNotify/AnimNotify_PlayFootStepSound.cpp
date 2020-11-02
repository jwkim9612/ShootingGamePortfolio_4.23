#include "AnimNotify_PlayFootStepSound.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SGFootStepSoundList.h"
#include "Sound/SoundCue.h"

void UAnimNotify_PlayFootStepSound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	
	SGCHECK(SoundListClass);
	if (SoundList == nullptr)
	{
		SoundList = SoundListClass->GetDefaultObject<USGFootStepSoundList>();
	}
	SGCHECK(SoundList);

	FHitResult HitResult;
	FVector Start = MeshComp->GetSocketLocation(SocketName);
	FVector End = Start + FVector(0.0f, 0.0f, -100.0f);
	
	TArray<AActor*> IgnoreActorList;
	IgnoreActorList.Add(MeshComp->GetOwner());
	EDrawDebugTrace::Type Debug = EDrawDebugTrace::None;
	UWorld* World = MeshComp->GetWorld();
	SGCHECK(World);

	bool bResult = UKismetSystemLibrary::LineTraceSingle(
		World, 
		Start, 
		End, 
		UEngineTypes::ConvertToTraceType(ECC_Visibility), 
		true, 
		IgnoreActorList, 
		Debug, 
		HitResult, 
		true
	);

	if (bResult)
	{
		if (HitResult.GetActor() == nullptr) 
			return;

		USoundCue* Sound = SoundList->GetSound(HitResult.PhysMaterial->GetName());
		if (Sound == nullptr)
			return;

		UGameplayStatics::SpawnSoundAtLocation(MeshComp->GetWorld(), Sound, HitResult.Location);
	}
}
