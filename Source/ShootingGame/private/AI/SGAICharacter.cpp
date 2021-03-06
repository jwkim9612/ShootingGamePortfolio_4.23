#include "SGAICharacter.h"
#include "SGPlayer.h"
#include "SGAIController.h"
#include "SGGameInstance.h"
#include "SGAICharacterAnimInstance.h"
#include "SGWeapon.h"
#include "AIService.h"
#include "SGAmmo.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

ASGAICharacter::ASGAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// 캐릭터 제작시 3차원 좌표계가 언리얼 3차원 좌표계와 다르기 때문에 Z축으로 -90도 회전시켜줘야한다
	// 또 액터의 기준 위치가 다르기 때문에 Z축으로 절반 높이만큼 내려줘야 한다.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetCharacterMovement()->MaxWalkSpeed = AIService::MaxWalkSpeed;

	AIPerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSourceComponent"));
	AIPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Sight::StaticClass());
}

void ASGAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SGAIController = Cast<ASGAIController>(GetController());
	SGCHECK(SGAIController);

	SGAICharacterAnimInstance = Cast<USGAICharacterAnimInstance>(GetMesh()->GetAnimInstance());
	SGCHECK(SGAICharacterAnimInstance);

	OnDead.AddUFunction(this, TEXT("DropItem"));
	OnDead.AddUFunction(this, TEXT("SetDeadCollision"));
	OnDead.AddUFunction(this, TEXT("SetDestroyTimer"));
	
	CreateWeapon();
}

float ASGAICharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	CurrentHealth = FMath::Clamp(CurrentHealth - static_cast<int>(Damage), 0, CurrentHealth);

	SGAIController->SetDetectedKey(true);
	SGAIController->SetTargetKey(DamageCauser);
	SetTarget(DamageCauser);

	if (CurrentHealth <= 0)
	{
		Dead();
	}

	return FinalDamage;
}

void ASGAICharacter::Fire(const FVector & TargetLocation)
{
	SGCHECK(SGWeapon);
	SGWeapon->Fire(TargetLocation);
}

void ASGAICharacter::SetDead(bool bDead)
{
	bIsDead = bDead;
}

void ASGAICharacter::SetDropAmmoClass(WeaponType Type)
{
	UBlueprint* SGAmmoBP = nullptr;
	switch (Type)
	{
	case WeaponType::Rifle:
		SGAmmoBP = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, TEXT("Blueprint'/Game/BluePrint/Pickup/BP_SGRifleAmmo.BP_SGRifleAmmo'")));
		break;
	case WeaponType::Pistol:
		SGAmmoBP = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, TEXT("Blueprint'/Game/BluePrint/Pickup/BP_SGPistolAmmo.BP_SGPistolAmmo'")));
		break;
	}

	SGCHECK(SGAmmoBP);
	DropAmmo = SGAmmoBP->GeneratedClass;
}

bool ASGAICharacter::IsDead() const
{
	return bIsDead;
}

USGAICharacterAnimInstance * ASGAICharacter::GetAnimInstance() const
{
	return SGAICharacterAnimInstance;
}

void ASGAICharacter::DropItem()
{
	SGCHECK(DropAmmo);
	GetWorld()->SpawnActor<ASGAmmo>(DropAmmo, GetActorLocation(), FRotator::ZeroRotator);
}

void ASGAICharacter::SetDeadCollision()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
	SGAIController->UnPossess();
	SGAIController->Destroy();
	SGWeapon->Destroy();
}

void ASGAICharacter::SetDestroyTimer()
{
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
		Destroy();
	}), 2.0f, false);
}

void ASGAICharacter::CreateWeapon()
{
	USGGameInstance* SGGameInstance = Cast<USGGameInstance>(GetGameInstance());
	SGCHECK(SGGameInstance);

	FSGWeaponData* WeaponData = SGGameInstance->GetRandomWeaponData();
	SGCHECK(WeaponData);

	SGWeapon = GetWorld()->SpawnActor<ASGWeapon>(WeaponData->Class, FVector::ZeroVector, FRotator::ZeroRotator);
	if (SGWeapon != nullptr)
	{
		SGWeapon->SetController(SGAIController);
		SGWeapon->SetControllingPawn(SGAIController->GetPawn());
		SGWeapon->CreateProjectilePool();
		SGWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Weapon_Attach"));
		SetDropAmmoClass(SGWeapon->GetWeaponType());
	}
}

void ASGAICharacter::Dead()
{
	if (bIsDead)
		return;

	bIsDead = true;
	OnDead.Broadcast();
}
