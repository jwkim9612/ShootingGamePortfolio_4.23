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
	if(ReloadAnimMontage == nullptr)
	{
		SGLOG(Error, TEXT("ReloadAnimMontage is null!!"));
		return 0.0f;
	}

	float PlayLength = ReloadAnimMontage->GetPlayLength();
	return PlayLength;
}

float USGPlayerAnimInstance::GetEquipLength()
{
	if (EquipMontage == nullptr)
	{
		SGLOG(Error, TEXT("EquipAnimMontage is null!!"));
		return 0.0f;
	}

	float PlayLength = EquipMontage->GetPlayLength();
	return PlayLength;
}

void USGPlayerAnimInstance::SetEquippingWeapon(ASGWeapon * Weapon)
{
	SGCHECK(Weapon);
	EquippingWeapon = Weapon;
}

FRotator USGPlayerAnimInstance::GetForwardAimRotation()
{
	auto ControlRotation = Player->GetControlRotation();
	auto ControlPitch = ControlRotation.Pitch;
	if (ControlPitch > 180)
	{
		ControlPitch = 360 - ControlPitch;
	}
	else
	{
		ControlPitch *= -1;
	}

	ControlPitch /= 3;

	return FRotator(0.0f, 0.0f, ControlPitch);
}

void USGPlayerAnimInstance::AnimNotify_EquipWeapon()
{
	SGCHECK(EquippingWeapon);
	EquippingWeapon->SetVisibility(true);
}
