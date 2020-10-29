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
	PrimaryActorTick.bCanEverTick = true;

	// 캐릭터 제작시 3차원 좌표계가 언리얼 3차원 좌표계와 다르기 때문에 Z축으로 -90도 회전시켜줘야한다
	// 또 액터의 기준 위치가 다르기 때문에 Z축으로 절반 높이만큼 내려줘야 한다.
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
	if (SGPlayerController != nullptr)
	{
		SGPlayerController->GetSGHUDWidget()->GetSGBossHPBar()->SetHPProgressBar(GetHPRatio());
	}
	
	OnDead.AddDynamic(this, &ASGBoss::SetDead);
	OnDead.AddDynamic(this, &ASGBoss::SetDeadCollision);

	CreateProjectilePool();
}

void ASGBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ASGBoss::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	CurrentHealth = FMath::Clamp(CurrentHealth - static_cast<int>(Damage), 0, CurrentHealth);
	SGPlayerController->GetSGHUDWidget()->GetSGBossHPBar()->SetHPProgressBar(GetHPRatio());

	if (CurrentHealth <= 0)
	{
		OnDead.Broadcast();
		SGPlayerController->GetSGHUDWidget()->PlayFadeOutBossHPBarAnimation();
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

void ASGBoss::SetDead()
{
	if (SGBossAnimInstance == nullptr)
	{
		SGLOG(Warning, TEXT("SGBossAnimInstance is null!!"));
		return;
	}

	SGBossAnimInstance->SetDead();
}

void ASGBoss::SetDeadCollision()
{
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SGBossAIController->UnPossess();
}
