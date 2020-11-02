#pragma once

#include "ShootingGame.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "SGPlayer.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnWeaponChangedDelegate);

UCLASS()
class SHOOTINGGAME_API ASGPlayer : public ACharacter, public IGenericTeamAgentInterface
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
	virtual FGenericTeamId GetGenericTeamId() const override;

public:
	int32 GetHealth() const;
	class ASGWeapon* GetCurrentWeapon() const;
	class ASGWeapon* GetRifle() const;
	class ASGWeapon* GetPistol() const;
	const FRotator GetSpringArmRotation() const;
	bool IsCrouching() const;
	bool IsSprint() const;
	bool IsReloading() const;
	bool IsAimDownSight() const;
	bool IsEquipping() const;
	bool IsDead() const;
	bool IsMoving() const;
	void SetCamera(CameraMode NewCameraMode);

private:
	void MoveUpDown(float AxisValue);
	void MoveRightLeft(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);
	void Sprint();
	void SprintOff();
	void DoCrouch();

private:
	void Fire();
	void FireOnCrossHair();
	void UnFire();
	void Recoil();
	void Reload();
	void AimDownSight();
	void AimDownSightOff();
	void SpreadCrossHair();

private:
	void CreateWeapon();
	void SelectRifle();
	void SelectPistol();
	void SelectWeapon(class ASGWeapon* Weapon);

private:
	UFUNCTION()
	void SetDead();
	void SetHealingTimer();

public:
	FOnWeaponChangedDelegate OnWeaponChanged;

private:
	FGenericTeamId TeamId;

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

	UPROPERTY()
	class USGCrossHair* SGCrossHair;

private:
	UPROPERTY(EditAnywhere, Category = "Stat")
	int32 Health;

	UPROPERTY(EditInstanceOnly, category = "camera", meta = (AllowPrivateAccess = true))
	float ArmLengthTo;

	UPROPERTY(EditInstanceOnly, category = "camera", meta = (AllowPrivateAccess = true))
	float ArmLengthSpeed;

	UPROPERTY(EditInstanceOnly, category = "camera", meta = (AllowPrivateAccess = true))
	FVector ArmLocation;

	UPROPERTY(EditInstanceOnly, category = "camera", meta = (AllowPrivateAccess = true))
	FRotator ArmRotation;

private:
	bool bIsHealing;
	bool bIsReloading;
	bool bIsCrouching;
	bool bIsSprint;
	bool bIsEquipping;
	bool bIsAimDownSight;
	bool bIsFiring;
	bool bIsDead;
	bool bIsPressedAimDownSight;
	bool bIsPressedSprint;

private:
	FTimerHandle HealingTimerHandle;
	FTimerHandle FireTimerHandle;
	FTimerHandle ReloadTimerHandle;
	FTimerHandle EquipTimerHandle;
};
