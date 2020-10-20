#include "SGPickupActor.h"

ASGPickupActor::ASGPickupActor()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	RootComponent = CapsuleComponent;
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ASGPickupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASGPickupActor::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

