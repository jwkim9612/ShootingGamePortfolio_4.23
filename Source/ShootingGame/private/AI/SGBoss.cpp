#include "SGBoss.h"
#include "SGBossAIController.h"

ASGBoss::ASGBoss()
{
	PrimaryActorTick.bCanEverTick = true;

	// ĳ���� ���۽� 3���� ��ǥ�谡 �𸮾� 3���� ��ǥ��� �ٸ��� ������ Z������ -90�� ȸ����������Ѵ�
	// �� ������ ���� ��ġ�� �ٸ��� ������ Z������ ���� ���̸�ŭ ������� �Ѵ�.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<ASGBossAIController> SGBossAIControllerClass(TEXT("Blueprint'/Game/BluePrint/AI/BP_SGBossAIController.BP_SGBossAIController_C'"));
	if (SGBossAIControllerClass.Succeeded())
	{
		AIControllerClass = SGBossAIControllerClass.Class;
	}
}

void ASGBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASGBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASGBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

