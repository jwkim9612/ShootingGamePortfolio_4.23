#include "SGAICharacter.h"
#include "SGPlayer.h"
#include "SGAIController.h"
#include "SGGameInstance.h"
#include "SGWeapon.h"
#include "AIService.h"
#include "SGAmmo.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

ASGAICharacter::ASGAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// ĳ���� ���۽� 3���� ��ǥ�谡 �𸮾� 3���� ��ǥ��� �ٸ��� ������ Z������ -90�� ȸ����������Ѵ�
	// �� ������ ���� ��ġ�� �ٸ��� ������ Z������ ���� ���̸�ŭ ������� �Ѵ�.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetCharacterMovement()->MaxWalkSpeed = AIService::MaxWalkSpeed;

	AIPerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSourceComponent"));
	AIPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Sight::StaticClass());
}

void ASGAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SGAIController = Cast<ASGAIController>(GetController());
	if (SGAIController == nullptr)
	{
		SGLOG(Warning, TEXT("No AIController!!"));
		return;
	}

	OnDead.AddDynamic(this, &ASGAICharacter::DropItem);
	OnDead.AddDynamic(this, &ASGAICharacter::SetDeadCollision);
	OnDead.AddDynamic(this, &ASGAICharacter::SetDestroyTimer);

	CreateWeapon();
}

void ASGAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ASGAICharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	CurrentHealth = FMath::Clamp(CurrentHealth - static_cast<int>(Damage), 0, CurrentHealth);

	if (CurrentHealth <= 0)
	{
		Dead();
	}

	return FinalDamage;
}

void ASGAICharacter::SetDead(bool bDead)
{
	bIsDead = bDead;
}

bool ASGAICharacter::IsDead() const
{
	return bIsDead;
}

void ASGAICharacter::DropItem()
{
	if (DropAmmo != nullptr)
	{
		GetWorld()->SpawnActor<ASGAmmo>(DropAmmo, GetActorLocation(), FRotator::ZeroRotator);
	}
}

void ASGAICharacter::SetDeadCollision()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
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
	}
}

void ASGAICharacter::Dead()
{
	if (bIsDead)
	{
		return;
	}

	bIsDead = true;
	OnDead.Broadcast();
}
