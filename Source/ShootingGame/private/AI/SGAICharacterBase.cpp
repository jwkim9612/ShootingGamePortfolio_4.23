#include "SGAICharacterBase.h"
#include "SGPlayer.h"

void ASGAICharacterBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void ASGAICharacterBase::Fire(const FVector & ShootDirection)
{
	SGLOG(Warning, TEXT("Fire"));
}

void ASGAICharacterBase::SetTarget(AActor * NewTarget)
{
	SGCHECK(NewTarget);
	Target = NewTarget;
}

AActor * ASGAICharacterBase::GetTarget() const
{
	return Target;
}

float ASGAICharacterBase::GetHPRatio() const
{
	float HPRatio = static_cast<float>(CurrentHealth) / MaxHealth;
	return HPRatio;
}
