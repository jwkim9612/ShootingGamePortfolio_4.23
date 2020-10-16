#include "SGAICharacter.h"
#include "SGPlayer.h"
#include "SGAIController.h"
#include "AIService.h"
#include "SGAmmo.h"
#include "Perception/PawnSensingComponent.h"

ASGAICharacter::ASGAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// ĳ���� ���۽� 3���� ��ǥ�谡 �𸮾� 3���� ��ǥ��� �ٸ��� ������ Z������ -90�� ȸ����������Ѵ�
	// �� ������ ���� ��ġ�� �ٸ��� ������ Z������ ���� ���̸�ŭ ������� �Ѵ�.
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
