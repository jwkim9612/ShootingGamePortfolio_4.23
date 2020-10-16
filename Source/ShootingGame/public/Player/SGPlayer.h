#pragma once

#include "ShootingGame.h"
#include "GameFramework/Character.h"
#include "SGPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponChangedDelegate);

UCLASS()
class SHOOTINGGAME_API ASGPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ASGPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	int32 GetHealth() const;
	class ASGWeapon* GetCurrentWeapon() const;
	class ASGWeapon* GetRifle() const;
	class ASGWeapon* GetPistol() const;

	void TakeHit();
	bool IsCrouching() const;
	bool IsSprint() const;
	bool IsReloading() const;
	bool IsAimDownSight() const;
	bool IsEquipping() const;

private:
	void MoveUpDown(float AxisValue);
	void MoveRightLeft(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);

	void SetHealingTimer();

	void Fire();
	void FireOnCrossHair();
	void UnFire();
	void Recoil();
	void Reload();
	void DoCrouch();
	void AimDownSight();
	void AimDownSightOff();
	void SetCamera(CameraMode NewCameraMode);
	void Sprint();
	void SprintOff();
	// 후에 이름 바꿀것. // 조준선 확산 처리.
	void SpreadCorssHairSetting();
	bool IsMoving();

	void CreateWeapon();
	void SelectRifle();
	void SelectPistol();

public:
	FOnWeaponChangedDelegate OnWeaponChanged;

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;

private:

	UPROPERTY()
	class ASGPlayerController* SGPlayerController;

	UPROPERTY()
	class ASGPlayerState* SGPlayerState;

	UPROPERTY()
	class USGPlayerAnimInstance* SGPlayerAnimInstance;

	UPROPERTY()
	class USGGameInstance* SGGameInstance;

	UPROPERTY()
	class ASGWeapon* CurrentWeapon;

	UPROPERTY()
	class ASGWeapon* Rifle;

	UPROPERTY()
	class ASGWeapon* Pistol;

	UPROPERTY()
	class USGWeaponHUD* SGWeaponHUD;
private:
	UPROPERTY(EditAnywhere, Category = "Stat")
	int32 Health;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	bool bIsHealing;

	bool bIsReloading;
	bool bIsCrouching;
	bool bIsSprint;
	bool bIsEquipping;
	bool bIsAimDownSight;
	bool bIsFiring;

	bool bIsPressedAimDownSight;
	bool bIsPressedSprint;

	UPROPERTY(EditInstanceOnly, category = "camera", meta = (AllowPrivateAccess = true))
	float ArmLengthTo;

	UPROPERTY(EditInstanceOnly, category = "camera", meta = (AllowPrivateAccess = true))
	float ArmLengthSpeed;

	UPROPERTY(EditInstanceOnly, category = "camera", meta = (AllowPrivateAccess = true))
	FVector ArmLocation;

private:
	FTimerHandle HealingTimerHandle;
	FTimerHandle FireTimerHandle;
	FTimerHandle ReloadTimerHandle;
	FTimerHandle EquipTimerHandle;
};
