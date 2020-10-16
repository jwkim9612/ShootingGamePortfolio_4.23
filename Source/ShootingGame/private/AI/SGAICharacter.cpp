#include "SGAICharacter.h"
#include "SGPlayer.h"
#include "SGAIController.h"
#include "AIService.h"
#include "SGAmmo.h"
#include "Perception/PawnSensingComponent.h"

ASGAICharacter::ASGAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// 캐릭터 제작시 3차원 좌표계가 언리얼 3차원 좌표계와 다르기 때문에 Z축으로 -90도 회전시켜줘야한다
	// 또 액터의 기준 위치가 다르기 때문에 Z축으로 절반 높이만큼 내려줘야 한다.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetCharacterMovement()->MaxWalkSpeed = AIService::MaxWalkSpeed;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SetPeripheralVisionAngle(AIService::PeripheralVisionAngle);

	Health = 100.0f;
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

	PawnSensing->OnSeePawn.AddDynamic(this, &ASGAICharacter::OnSeePlayer);

}

void ASGAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ASGAICharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	Health = FMath::Clamp(Health - static_cast<int>(Damage), 0, Health);

	if (Health <= 0)
	{
		DropItem();
		Destroy();
	}

	return FinalDamage;
}

void ASGAICharacter::OnSeePlayer(APawn * Pawn)
{
	ASGPlayer* Player = Cast<ASGPlayer>(Pawn);
	if (Player != nullptr)
	{
		SGAIController->MoveToActor(Player, 50.0f);
	}
}

void ASGAICharacter::DropItem()
{
	if (DropAmmo != nullptr)
	{
		GetWorld()->SpawnActor<ASGAmmo>(DropAmmo, GetActorLocation(), FRotator::ZeroRotator);
	}
}
