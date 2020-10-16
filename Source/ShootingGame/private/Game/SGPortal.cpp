#include "SGPortal.h"
#include "SGPlayerController.h"
#include "SGGameInstance.h"
#include "SGPlayerState.h"
#include "SGHUDWidget.h"

ASGPortal::ASGPortal()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));

	RootComponent = CapsuleComponent;
	ParticleSystem->SetupAttachment(RootComponent);

	CapsuleComponent->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

void ASGPortal::BeginPlay()
{
	Super::BeginPlay();
	
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ASGPortal::OnOverlapBegin);

	SGGameInstance = Cast<USGGameInstance>(GetGameInstance());
	SGPlayerController = Cast<ASGPlayerController>(GetWorld()->GetFirstPlayerController());
	if (SGPlayerController != nullptr)
	{
		SGHUDWidget = SGPlayerController->GetSGHUDWidget();
	}
}

void ASGPortal::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	SGCHECK(SGHUDWidget);
	float AnimationLength = SGHUDWidget->PlayFadeOutScreenAnimation();
	
	ASGPlayerState* SGPlayerState = SGPlayerController->GetPlayerState<ASGPlayerState>();
	SGCHECK(SGPlayerState);

	SGPlayerState->SavePlayerData();
	SetLoadStageTimer(AnimationLength);
}

void ASGPortal::SetLoadStageTimer(float LoadStageTimer)
{
	GetWorld()->GetTimerManager().SetTimer(LoadStageTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
		SGGameInstance->LoadNextStage();
	}), LoadStageTimer, false);
}
