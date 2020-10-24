#include "SGProjectile.h"
#include "SGGameInstance.h"
#include "SGAICharacter.h"
#include "ProjectileService.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASGProjectile::ASGProjectile()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	
	BoxComponent->SetCollisionProfileName(TEXT("Projectile"));
	SetRootComponent(BoxComponent);
	MeshComponent->SetupAttachment(RootComponent);
	ParticleSystemComponent->SetupAttachment(MeshComponent);

	MovementComponent->InitialSpeed = ProjectileService::DefaultInitialSpeed;
	MovementComponent->MaxSpeed = ProjectileService::DefaultMaxSpeed;

	// 중력
	MovementComponent->ProjectileGravityScale = ProjectileService::DefaultProjectileGravityScale;
}

void ASGProjectile::BeginPlay()
{
	Super::BeginPlay();

	SGGameInstance = Cast<USGGameInstance>(GetWorld()->GetGameInstance());
	SGCHECK(SGGameInstance);

	BoxComponent->OnComponentHit.AddDynamic(this, &ASGProjectile::OnHit);
}

// 발사체의 속도를 발사 방향으로 초기화시키는 함수입니다.
void ASGProjectile::FireInDirection(const FVector & ShootDirection)
{
	MovementComponent->Velocity = ShootDirection * MovementComponent->InitialSpeed;
	BoxComponent->SetRelativeRotation(ShootDirection.Rotation());
}

void ASGProjectile::Disable()
{
	MovementComponent->SetVelocityInLocalSpace(FVector::ZeroVector);
	MovementComponent->ProjectileGravityScale = 0.0f;
	MovementComponent->Deactivate();
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void ASGProjectile::Activate()
{
	MovementComponent->ProjectileGravityScale = 0.05f;
	MovementComponent->Activate(true);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	//SetDisableTimer(ProjectileService::DisableTimer);
}

void ASGProjectile::SetController(AController * NewController)
{
	SGCHECK(NewController);
	Controller = NewController;
}

void ASGProjectile::SetControllingPawn(APawn * NewPawn)
{
	SGCHECK(NewPawn);
	ControllingPawn = NewPawn;
}

void ASGProjectile::SetInitialSpeed(float NewSpeed)
{
	MovementComponent->InitialSpeed = NewSpeed;
}

int32 ASGProjectile::GetDamage() const
{
	return Damage;
}

void ASGProjectile::SetDisableTimer(float DisableTimer)
{
	GetWorld()->GetTimerManager().SetTimer(DisableTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
		Disable();
	}), DisableTimer, false);
}

void ASGProjectile::ClearDisableTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(DisableTimerHandle);
}

void ASGProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UParticleSystem* ParticleSystem;
	ACharacter* TargetCharacter = Cast<ACharacter>(OtherActor);
	if (TargetCharacter != nullptr)
	{
		//if (TargetActor->IsDead())
		//{
		//	SGLOG(Warning, TEXT("Return"));
		//	return;
		//}

		FDamageEvent DamageEvent;
		float FinalDamage;

		if (Hit.BoneName.ToString().Equals(TEXT("head")))
		{
			FinalDamage = Damage * 2;
			SGGameInstance->PlayFloatingDamageText(Damage * 2.0f, Hit.Location, true);
		}
		else
		{
			FinalDamage = Damage;
			SGGameInstance->PlayFloatingDamageText(Damage, Hit.Location);
		}

		TargetCharacter->TakeDamage(FinalDamage, DamageEvent, Controller, ControllingPawn);
		ParticleSystem = SGGameInstance->TryGetParticleSystem(FString("HitCharacter"));
	}
	else
	{
		ParticleSystem = SGGameInstance->TryGetParticleSystem(FString("HitWall"));
	}

	auto Particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, Hit.Location);
	Particle->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	//ClearDisableTimer();
	Disable();
}
