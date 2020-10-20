#include "SGStar.h"

ASGStar::ASGStar()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent->SetCapsuleHalfHeight(90.0f);
	CapsuleComponent->SetCapsuleRadius(50.0f);
	StaticMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -60.0f));
}

void ASGStar::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ASGStar::OnOverlapBegin);
}

void ASGStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StaticMeshComponent->AddRelativeRotation(FRotator(0.0f, 1.0f, 0.0f));
}

void ASGStar::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	OnPickup.Broadcast();
	Destroy();
}

