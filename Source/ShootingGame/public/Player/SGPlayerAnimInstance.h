#pragma once

#include "ShootingGame.h"
#include "Animation/AnimInstance.h"
#include "SGPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()



private:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	float GetReloadLength();
	float GetEquipLength();

	void SetEquippingWeapon(class ASGWeapon* Weapon);

private:
	FRotator GetForwardAimRotation();

private:
	UFUNCTION()
	void AnimNotify_EquipWeapon();

private:
	UPROPERTY()
	class ASGPlayer* Player;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	float CurrentSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	float Direction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	bool bIsInAir;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	bool bIsCrouching;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	bool bIsSprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	bool bIsAimDownSight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	bool bIsReloading;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	bool bIsEquipping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	FRotator AimRotation;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	UAnimMontage* ReloadAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	UAnimMontage* EquipMontage;

	UPROPERTY()
	class ASGWeapon* EquippingWeapon;
};
