#include "SGKey.h"

ASGKey::ASGKey()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -45.0f));
	StaticMeshComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
}

void ASGKey::BeginPlay()
{
	Super::BeginPlay();
	
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ASGKey::OnOverlapBegin);
}

void ASGKey::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	StaticMeshComponent->AddRelativeRotation(FRotator(0.0f, 1.0f, 0.0f));
}

void ASGKey::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	OnPickup.Broadcast();
	Destroy();
}
