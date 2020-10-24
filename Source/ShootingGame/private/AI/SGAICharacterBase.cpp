#include "SGAICharacterBase.h"
#include "SGPlayer.h"

ASGAICharacterBase::ASGAICharacterBase()
{
}

void ASGAICharacterBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void ASGAICharacterBase::Fire(const FVector & ShootDirection)
{
	SGLOG(Warning, TEXT("Fire"));
}

void ASGAICharacterBase::SetTarget(ASGPlayer * NewTarget)
{
	SGCHECK(NewTarget);
	Target = NewTarget;
}

ASGPlayer * ASGAICharacterBase::GetTarget() const
{
	return Target;
}

float ASGAICharacterBase::GetHPRatio() const
{
	float HPRatio = static_cast<float>(CurrentHealth) / MaxHealth;
	return HPRatio;
}
