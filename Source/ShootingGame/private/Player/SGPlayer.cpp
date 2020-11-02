#include "SGPlayer.h"
#include "SGPlayerController.h"
#include "SGPlayerState.h"
#include "PlayerService.h"
#include "SGHitEffect.h"
#include "SGHUDWidget.h"
#include "SGWeapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SGPlayerAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "SGCrossHair.h"
#include "Kismet/KismetMathLibrary.h"
#include "SGGameInstance.h"
#include "SGWeaponHUD.h"

ASGPlayer::ASGPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// 캐릭터 제작시 3차원 좌표계가 언리얼 3차원 좌표계와 다르기 때문에 Z축으로 -90도 회전시켜줘야한다
	// 또 액터의 기준 위치가 다르기 때문에 Z축으로 절반 높이만큼 내려줘야 한다.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	ArmLengthSpeed = 2.0f;

	bIsCrouching = false;
	bIsSprint = false;
	bIsReloading = false;
	bIsAimDownSight = false;
	bIsEquipping = false;
	bIsFiring = false;
	bIsDead = false;
	bIsPressedAimDownSight = false;

	TeamId = FGenericTeamId(0);
}

void ASGPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	SGPlayerController = Cast<ASGPlayerController>(GetController());
	SGCHECK(SGPlayerController);

	SGPlayerState = Cast<ASGPlayerState>(SGPlayerController->PlayerState);
	SGCHECK(SGPlayerState);

	SGPlayerAnimInstance = Cast<USGPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	SGCHECK(SGPlayerAnimInstance);

	SGGameInstance = Cast<USGGameInstance>(GetWorld()->GetGameInstance());
	SGCHECK(SGGameInstance);

	SGWeaponHUD = Cast<USGWeaponHUD>(SGPlayerController->GetSGHUDWidget()->GetWeaponHUD());
	SGCHECK(SGWeaponHUD);

	SGCrossHair = Cast<USGCrossHair>(SGPlayerController->GetSGHUDWidget()->GetSGCrossHair());
	SGCHECK(SGCrossHair);

	SGPlayerState->InitPlayerData(this);
	SGPlayerState->OnHPIsZero.AddUFunction(this, TEXT("SetDead"));

	SetCamera(CameraMode::UnAiming);
	SetCamera(CameraMode::Stand);

	CreateWeapon();
}

void ASGPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/////////// 조준. 점프중에 조준키 눌렀을 때, 장전 조준키 눌렀을 때 처리 /////////////
	if (bIsPressedAimDownSight)
	{
		if (!bIsAimDownSight && !bIsSprint && !GetCharacterMovement()->IsFalling() && !bIsReloading && !bIsEquipping)
		{
			bIsAimDownSight = true;
			SGCrossHair->SetDefaultSpreadValue(PlayerService::DefaultAimSpreadValue);
			SetCamera(CameraMode::Aiming);
		}
	}
	//////////////////////////////////////////////////////////////////////////

	/////////// 달리기처리 /////////////
	if (bIsPressedSprint)
	{
		if (!bIsSprint && GetVelocity().Size() > 0 && !GetCharacterMovement()->IsFalling() && !bIsCrouching && !bIsReloading && !bIsAimDownSight)
		{
			bIsSprint = true;
			GetCharacterMovement()->MaxWalkSpeed = PlayerService::SprintMaxWalkSpeed;
		}
	}
	//////////////////////////////////////////////////////////////////////////

	/////////// 카메라 부드럽게 처리 ///////////////////////////////////////////
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaSeconds, ArmLengthSpeed);
	SpringArm->SetRelativeLocation(FMath::VInterpTo(SpringArm->GetRelativeTransform().GetLocation(), ArmLocation, DeltaSeconds, ArmLengthSpeed));
	
	// 사망시에 Mesh를 Ragdoll로 바꿔서 다른곳으로 이동하는데 Capsule은 가만히 있음. 
	// 그런데 카메라가 Capsule을 따라가기 때문에 Capsule을 Mesh 위치로 이동.
	if (bIsDead)
	{
		GetCapsuleComponent()->SetRelativeLocation(GetMesh()->GetComponentLocation());
		SpringArm->SetRelativeRotation(FMath::RInterpTo(SpringArm->GetRelativeTransform().GetRotation().Rotator(), ArmRotation, DeltaSeconds, ArmLengthSpeed));
	}

	////////////////////////////////////////////////////////////////////////////

	/////////////////////// 힐 처리 ////////////////////////////////////////////
	if (!bIsDead)
	{
		if (bIsHealing)
		{
			if (SGPlayerState->IsMaxHP())
			{
				SGPlayerController->GetSGHUDWidget()->PlayFadeOutHPBarAnimation();
				bIsHealing = false;
			}
			else
			{
				SGPlayerState->HealHP();
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////
}

void ASGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ASGPlayer::Jump);
	PlayerInputComponent->BindAction(TEXT("PrimaryFire"), EInputEvent::IE_Pressed, this, &ASGPlayer::Fire);
	PlayerInputComponent->BindAction(TEXT("PrimaryFire"), EInputEvent::IE_Released, this, &ASGPlayer::UnFire);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &ASGPlayer::DoCrouch);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &ASGPlayer::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &ASGPlayer::SprintOff);
	PlayerInputComponent->BindAction(TEXT("AimDownSight"), EInputEvent::IE_Pressed, this, &ASGPlayer::AimDownSight);
	PlayerInputComponent->BindAction(TEXT("AimDownSight"), EInputEvent::IE_Released, this, &ASGPlayer::AimDownSightOff);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &ASGPlayer::Reload);
	PlayerInputComponent->BindAction(TEXT("SelectRifle"), EInputEvent::IE_Pressed, this, &ASGPlayer::SelectRifle);
	PlayerInputComponent->BindAction(TEXT("SelectPistol"), EInputEvent::IE_Pressed, this, &ASGPlayer::SelectPistol);
	PlayerInputComponent->BindAxis(TEXT("MoveUpDown"), this, &ASGPlayer::MoveUpDown);
	PlayerInputComponent->BindAxis(TEXT("MoveRightLeft"), this, &ASGPlayer::MoveRightLeft);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ASGPlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASGPlayer::LookUp);
}

void ASGPlayer::Jump()
{
	if (bIsCrouching)
	{
		DoCrouch();
	}
	else
	{
		Super::Jump();
	}
}

float ASGPlayer::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	SetHealingTimer();

	SGPlayerState->SetHPToDamage(FinalDamage);
	SGPlayerController->GetSGHUDWidget()->PlayFadeHitEffectAnimation();
	SGPlayerController->GetSGHUDWidget()->PlayFadeInHPBarAnimation();

	return FinalDamage;
}

int32 ASGPlayer::GetHealth() const
{
	return Health;
}

ASGWeapon * ASGPlayer::GetCurrentWeapon() const
{
	return CurrentWeapon;
}

ASGWeapon * ASGPlayer::GetRifle() const
{
	return Rifle;
}

ASGWeapon * ASGPlayer::GetPistol() const
{
	return Pistol;
}

const FRotator ASGPlayer::GetSpringArmRotation() const
{
	return SpringArm->GetRelativeTransform().GetRotation().Rotator();
}

FGenericTeamId ASGPlayer::GetGenericTeamId() const
{
	return TeamId;
}

bool ASGPlayer::IsCrouching() const
{
	return bIsCrouching;
}

bool ASGPlayer::IsSprint() const
{
	return bIsSprint;
}

bool ASGPlayer::IsReloading() const
{
	return bIsReloading;
}

bool ASGPlayer::IsAimDownSight() const
{
	return bIsAimDownSight;
}

bool ASGPlayer::IsEquipping() const
{
	return bIsEquipping;
}

bool ASGPlayer::IsDead() const
{
	return bIsDead;
}

void ASGPlayer::MoveUpDown(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ASGPlayer::MoveRightLeft(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void ASGPlayer::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ASGPlayer::LookUp(float AxisValue)
{
	float SpringArmPitchValue = GetSpringArmRotation().Pitch;
	// 마우스를 아래로 했을 경우
	if (AxisValue > 0)
	{
		if (SpringArmPitchValue > -60)
		{
			SpringArm->AddRelativeRotation(FRotator(-AxisValue, 0.0f, 0.0f));
		}
	}
	// 마우스를 위로 했을 경우
	else if (AxisValue < 0)
	{
		if (SpringArmPitchValue < 60)
		{
			SpringArm->AddRelativeRotation(FRotator(-AxisValue, 0.0f, 0.0f));
		}
	}
}

void ASGPlayer::SetHealingTimer()
{
	bIsHealing = false;

	GetWorld()->GetTimerManager().ClearTimer(HealingTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(HealingTimerHandle, FTimerDelegate::CreateLambda([this]() -> void
	{
		bIsHealing = true;
	}), PlayerService::HealingTimer, false);
}

void ASGPlayer::Fire()
{
	SGCHECK(CurrentWeapon);
	if (!CurrentWeapon->HasAmmo() || bIsReloading || bIsSprint || bIsEquipping)
		return;

	FireOnCrossHair();
	if (CurrentWeapon->GetWeaponType() == WeaponType::Pistol)
		return;
	
	bIsFiring = true;
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, FTimerDelegate::CreateLambda([this]() -> void
	{
		if (CurrentWeapon->HasAmmo())
		{
			FireOnCrossHair();
		}
		else
		{
			UnFire();
		}
	}), CurrentWeapon->GetFireRate(), true);
}

void ASGPlayer::FireOnCrossHair()
{
	float SpreadValue = SGPlayerController->GetSGHUDWidget()->GetSGCrossHair()->GetSpreadValue();
	float RandomYawValue = FMath::RandRange(-SpreadValue, SpreadValue) * 0.1f;
	float RandomPitchValue = FMath::RandRange(-SpreadValue, SpreadValue) * 0.1f;

	FRotator FinalRotation = UKismetMathLibrary::ComposeRotators(FRotator(RandomPitchValue, RandomYawValue, 0.0f), Camera->GetComponentToWorld().GetRotation().Rotator());
	FVector FinalVector = UKismetMathLibrary::GetForwardVector(FinalRotation);

	FHitResult HitResult;
	FVector Start = Camera->GetComponentToWorld().GetLocation();
	FVector End = FinalVector * 100000 + Start;

	//DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 10.0f, ESceneDepthPriorityGroup::SDPG_World, 2.0f);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility))
	{
		CurrentWeapon->Fire(HitResult.ImpactPoint);
	}
	else
	{
		CurrentWeapon->Fire(HitResult.TraceEnd);
	}

	Recoil();
	SpreadCrossHair();
}

void ASGPlayer::UnFire()
{
	bIsFiring = false;
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void ASGPlayer::Recoil()
{
	float RecoliPitchValue = CurrentWeapon->GetRecoli();
	float RecoliYawValue = FMath::RandRange(-RecoliPitchValue, RecoliPitchValue);

	SpringArm->AddRelativeRotation(FRotator(RecoliPitchValue, 0.0f, 0.0f));
	AddControllerYawInput(RecoliYawValue);
}

void ASGPlayer::Reload()
{
	if (CurrentWeapon->IsFullAmmo() || bIsReloading || bIsAimDownSight || !CurrentWeapon->HasMaxAmmo() || bIsSprint || GetCharacterMovement()->IsFalling() || bIsEquipping)
	{
		return;
	}

	bIsReloading = true;

	CurrentWeapon->PlayReloadSound();
	float PlayDuration = SGPlayerAnimInstance->GetReloadLength();

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, FTimerDelegate::CreateLambda([this]() -> void
	{
		CurrentWeapon->Reload();
		bIsReloading = false;
	}), PlayDuration, false);
}

void ASGPlayer::DoCrouch()
{
	if (GetMovementComponent()->IsFalling() || bIsSprint)
		return;

	if (bIsCrouching)
	{
		bIsCrouching = false;
		SetCamera(CameraMode::Stand);
		GetCharacterMovement()->MaxWalkSpeed = PlayerService::DefaultMaxWalkSpeed;
	}
	else
	{
		bIsCrouching = true;
		SetCamera(CameraMode::Crouch);
		GetCharacterMovement()->MaxWalkSpeed = PlayerService::CrouchMaxWalkSpeed;
	}
}

void ASGPlayer::AimDownSight()
{
	bIsPressedAimDownSight = true;
}

void ASGPlayer::AimDownSightOff()
{
	bIsPressedAimDownSight = false;
	bIsAimDownSight = false;
	SGCrossHair->SetDefaultSpreadValue(PlayerService::DefaultUnAimSpreadValue);
	SetCamera(CameraMode::UnAiming);
}

void ASGPlayer::SetCamera(CameraMode NewCameraMode)
{
	switch (NewCameraMode)
	{
	case CameraMode::UnAiming:
		ArmLengthTo = 150.0f;
		break;
	case CameraMode::Aiming:
		ArmLengthTo = 100.0f;
		break;
	case CameraMode::Stand:
		ArmLocation = FVector(0.0f, 65.0f, 90.0f);
		break;
	case CameraMode::Crouch:
		ArmLocation = FVector(0.0f, 65.0f, 40.0f);
		break;
	case CameraMode::Dead:
		ArmRotation = FRotator(-90.0f, 0.0f, 0.0f);
		ArmLocation = FVector(90.0f, 0.0f, 90.0f);
		ArmLengthTo = 500.0f;
		break;
	}
}

void ASGPlayer::Sprint()
{
	bIsPressedSprint = true;
}

void ASGPlayer::SprintOff()
{
	bIsPressedSprint = false;

	if (bIsSprint)
	{
		bIsSprint = false;
		GetCharacterMovement()->MaxWalkSpeed = PlayerService::DefaultMaxWalkSpeed;
	}
}

void ASGPlayer::SpreadCrossHair()
{
	if (bIsAimDownSight)
	{
		if (IsMoving())
		{
			SGCrossHair->SetCurrentSpreadValue(40.0f);
		}
		else
		{
			SGCrossHair->SetCurrentSpreadValue(20.0f);
		}
	}
	else
	{
		if (IsMoving())
		{
			SGCrossHair->SetCurrentSpreadValue(80.0f);
		}
		else
		{
			SGCrossHair->SetCurrentSpreadValue(50.0f);
		}
	}
}

bool ASGPlayer::IsMoving() const
{
	if (GetCharacterMovement()->Velocity.Size() > 0)
	{
		return true;
	}

	return false;
}

void ASGPlayer::CreateWeapon()
{
	FString RifleName = SGGameInstance->GetSelectedRifleName();
	FString PistolName = SGGameInstance->GetSelectedPistolName();

	FSGWeaponData* RifleData = SGGameInstance->TryGetWeaponData(RifleName);
	SGCHECK(RifleData);

	Rifle = GetWorld()->SpawnActor<ASGWeapon>(RifleData->Class, FVector::ZeroVector, FRotator::ZeroRotator);
	if (Rifle != nullptr)
	{
		Rifle->SetController(SGPlayerController);
		Rifle->SetControllingPawn(this);
		Rifle->InitializeAmmo();
		Rifle->CreateProjectilePool();
		Rifle->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Weapon_Attach"));
	}

	FSGWeaponData* PistolData = SGGameInstance->TryGetWeaponData(PistolName);
	SGCHECK(PistolData);

	Pistol = GetWorld()->SpawnActor<ASGWeapon>(PistolData->Class, FVector::ZeroVector, FRotator::ZeroRotator);
	if (Pistol != nullptr)
	{
		Pistol->SetController(SGPlayerController);
		Pistol->SetControllingPawn(this);
		Pistol->InitializeAmmo();
		Pistol->CreateProjectilePool();
		Pistol->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Weapon_Attach"));
	}

	SGWeaponHUD->BindWeapon(Rifle);
	SGWeaponHUD->BindWeapon(Pistol);

	SelectRifle();
}

void ASGPlayer::SelectRifle()
{
	SelectWeapon(Rifle);
}

void ASGPlayer::SelectPistol()
{
	SelectWeapon(Pistol);
}

void ASGPlayer::SelectWeapon(ASGWeapon * Weapon)
{
	SGCHECK(Weapon);
	if (CurrentWeapon == Weapon || bIsEquipping || bIsSprint || GetCharacterMovement()->IsFalling())
	{
		return;
	}

	if (bIsReloading)
	{
		bIsReloading = false;
		GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle);
	}

	if (bIsFiring)
	{
		UnFire();
	}

	bIsAimDownSight = false;
	bIsEquipping = true;
	auto EquipTimer = SGPlayerAnimInstance->GetEquipLength();
	SGPlayerAnimInstance->SetEquippingWeapon(Weapon);
	Rifle->SetVisibility(false);

	GetWorld()->GetTimerManager().SetTimer(EquipTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
		bIsEquipping = false;
	}), EquipTimer, false);

	CurrentWeapon = Weapon;
	SGWeaponHUD->SetCurrentWeapon(CurrentWeapon);
	OnWeaponChanged.Broadcast();
}

void ASGPlayer::SetDead()
{
	bIsDead = true;
	
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
	DisableInput(SGPlayerController);
	SetCamera(CameraMode::Dead);
	TeamId = FGenericTeamId(1);

	float DiedAnimationLength = SGPlayerController->GetSGHUDWidget()->PlayFadeDiedAnimation();
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
		SGGameInstance->LoadMainMenu();
	}), DiedAnimationLength, false);
}
