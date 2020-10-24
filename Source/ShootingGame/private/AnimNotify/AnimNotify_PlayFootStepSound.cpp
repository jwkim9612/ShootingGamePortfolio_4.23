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
	FVector End = Start + FVector(0.0f, 0.0f, -500.0f);
	//FCollisionQueryParams CollisionParams;
	//CollisionParams.AddIgnoredActor(this);

	///// PhysMaterial이 Null로 나와서 아래 UKismetSystemLibrary를 사용.
	//if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_WorldStatic, CollisionParams))
	//{
	//	DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 10.0f, ESceneDepthPriorityGroup::SDPG_World, 2.0f);
	//	SGLOG(Warning, TEXT("%s"), *HitResult.Actor->GetName());
	//	if (HitResult.PhysMaterial != nullptr)
	//	{
	//		SGLOG(Warning, TEXT("%s"), *HitResult.PhysMaterial->GetName());
	//	}
	//	else
	//	{
	//		SGLOG(Warning, TEXT("No PhysMaterial"));
	//	}
	//}
	
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
