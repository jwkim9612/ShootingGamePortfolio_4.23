#include "SGPlayerAnimInstance.h"
#include "SGPlayer.h"
#include "SGWeapon.h"

void USGPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Player = Cast<ASGPlayer>(TryGetPawnOwner());
	SGCHECK(Player);
}

void USGPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Player != nullptr)
	{
		CurrentSpeed = Player->GetVelocity().Size();
		Direction = CalculateDirection(Player->GetVelocity(), Player->GetActorRotation());
		bIsInAir = Player->GetMovementComponent()->IsFalling();
		bIsCrouching = Player->IsCrouching();
		bIsSprint = Player->IsSprint();
		bIsAimDownSight = Player->IsAimDownSight();
		bIsReloading = Player->IsReloading();
		bIsEquipping = Player->IsEquipping();
		AimRotation = GetForwardAimRotation();
	}
}

float USGPlayerAnimInstance::GetReloadLength()
{
	return GetMontageLength(ReloadAnimMontage);
}

float USGPlayerAnimInstance::GetEquipLength()
{
	return GetMontageLength(EquipMontage);
}

float USGPlayerAnimInstance::GetMontageLength(class UAnimMontage* AnimMontage)
{
	if (AnimMontage == nullptr)
	{
		SGLOG(Error, TEXT("AnimMontage is null!!"));
		return 0.0f;
	}

	float PlayLength = AnimMontage->GetPlayLength();
	return PlayLength;
}

void USGPlayerAnimInstance::SetEquippingWeapon(ASGWeapon * Weapon)
{
	SGCHECK(Weapon);
	EquippingWeapon = Weapon;
}

FRotator USGPlayerAnimInstance::GetForwardAimRotation()
{
	float SpringArmPitch = Player->GetSpringArmRotation().Pitch;
	return FRotator(0.0f, 0.0f, -SpringArmPitch * 0.3f);
}

void USGPlayerAnimInstance::AnimNotify_EquipWeapon()
{
	SGCHECK(EquippingWeapon);
	EquippingWeapon->SetVisibility(true);
}
