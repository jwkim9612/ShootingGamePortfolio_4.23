#include "SGBoss.h"
#include "SGBossAIController.h"
#include "SGBossAnimInstance.h"
#include "SGProjectile.h"
#include "SGPlayerController.h"
#include "ProjectileService.h"
#include "SGHUDWidget.h"
#include "SGHPBar.h"
#include "SGPlayer.h"
#include "Kismet/KismetMathLibrary.h"

ASGBoss::ASGBoss()
{
	PrimaryActorTick.bCanEverTick = false;

	// ĳ���� ���۽� 3���� ��ǥ�谡 �𸮾� 3���� ��ǥ��� �ٸ��� ������ Z������ -90�� ȸ����������Ѵ�
	// �� ������ ���� ��ġ�� �ٸ��� ������ Z������ ���� ���̸�ŭ ������� �Ѵ�.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<ASGBossAIController> SGBossAIControllerClass(TEXT("Blueprint'/Game/BluePrint/AI/Boss/BP_SGBossAIController.BP_SGBossAIController_C'"));
	if (SGBossAIControllerClass.Succeeded())
	{
		AIControllerClass = SGBossAIControllerClass.Class;
	}
}

void ASGBoss::BeginPlay()
{
	Super::BeginPlay();
	
	SGBossAnimInstance = Cast<USGBossAnimInstance>(GetMesh()->GetAnimInstance());
	SGBossAIController = Cast<ASGBossAIController>(GetController());
	SGPlayerController = Cast<ASGPlayerController>(GetGameInstance()->GetPrimaryPlayerController());

	OnDead.AddUFunction(this, TEXT("SetDead"));
	OnDead.AddUFunction(this, TEXT("SetDeadCollision"));

	UpdateHPBar();
	CreateProjectilePool();
}

float ASGBoss::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	SetHPToDamage(Damage);
	UpdateHPBar();

	if (CurrentHealth <= 0)
	{
		OnDead.Broadcast();
		FadeOutHPBar();
	}

	return FinalDamage;
}

void ASGBoss::Fire(const FVector& TargetLocation)
{
	FVector MuzzleLocation = GetMesh()->GetSocketLocation("Muzzle");
	FRotator FinalRotation = UKismetMathLibrary::FindLookAtRotation(MuzzleLocation, TargetLocation);
	FVector LaunchDirection = FinalRotation.Vector();

	ASGProjectile* CurrentProjectile = ProjectilePool[ProjectileIndex];
	CurrentProjectile->SetActorLocation(MuzzleLocation);
	CurrentProjectile->FireInDirection(LaunchDirection);
	CurrentProjectile->Activate();

	++ProjectileIndex;
	if (ProjectileIndex == ProjectilePoolSize)
	{
		ProjectileIndex = 0;
	}
}

void ASGBoss::CreateProjectilePool()
{
	ProjectilePool.Reserve(ProjectilePoolSize);

	UWorld* World = GetWorld();
	SGCHECK(World);
	
	for (int i = 0; i < ProjectilePoolSize; ++i)
	{
		ASGProjectile* Projectile = World->SpawnActor<ASGProjectile>(ProjectileClass, FVector::ZeroVector, FRotator::ZeroRotator);
		SGCHECK(Projectile);
		Projectile->SetControllingPawn(this);
		Projectile->SetController(GetController());
		Projectile->SetInitialSpeed(ProjectileService::BossInitialSpeed);
		Projectile->Disable();
		ProjectilePool.Push(Projectile);
	}

	ProjectileIndex = 0;
}

void ASGBoss::UpdateHPBar()
{
	SGCHECK(SGBossAIController);
	SGPlayerController->GetSGHUDWidget()->GetSGBossHPBar()->SetHPProgressBar(GetHPRatio());
}

void ASGBoss::SetHPToDamage(float Damage)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - static_cast<int>(Damage), 0, CurrentHealth);
}

void ASGBoss::FadeOutHPBar()
{
	SGCHECK(SGPlayerController);
	SGPlayerController->GetSGHUDWidget()->PlayFadeOutBossHPBarAnimation();
}

void ASGBoss::SetDead()
{
	SGCHECK(SGBossAnimInstance);
	SGBossAnimInstance->SetDead();
}

void ASGBoss::SetDeadCollision()
{
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SGBossAIController->UnPossess();
}
