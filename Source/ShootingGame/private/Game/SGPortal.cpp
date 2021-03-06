#include "SGPortal.h"
#include "SGPlayerController.h"
#include "SGPlayer.h"
#include "SGGameInstance.h"
#include "SGPlayerState.h"
#include "SGHUDWidget.h"
#include "SGLevelScriptActorBase.h"

ASGPortal::ASGPortal()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));

	RootComponent = CapsuleComponent;
	ParticleSystem->SetupAttachment(RootComponent);

	CapsuleComponent->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	Disable();
}

void ASGPortal::BeginPlay()
{
	Super::BeginPlay();
	
	bIsPlayerEntered = false;

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ASGPortal::OnOverlapBegin);

	SGGameInstance = Cast<USGGameInstance>(GetGameInstance());
	SGCHECK(SGGameInstance);
	
	SGPlayerController = Cast<ASGPlayerController>(GetWorld()->GetFirstPlayerController());
	SGCHECK(SGPlayerController);
	
	SGHUDWidget = SGPlayerController->GetSGHUDWidget();
	SGCHECK(SGHUDWidget);

	auto SGLevelScriptActor = Cast<ASGLevelScriptActorBase>(GetWorld()->GetLevelScriptActor());
	SGCHECK(SGLevelScriptActor);

	SGLevelScriptActor->OnQuestComplete.AddUFunction(this, TEXT("Activate"));
}

void ASGPortal::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bIsPlayerEntered)
		return;

	bIsPlayerEntered = true;

	SGCHECK(SGHUDWidget);
	float AnimationLength = SGHUDWidget->PlayFadeOutScreenAnimation();
	
	ASGPlayerState* SGPlayerState = SGPlayerController->GetPlayerState<ASGPlayerState>();
	SGCHECK(SGPlayerState);

	SGPlayerState->SavePlayerData();
	SetLoadNextStageTimer(AnimationLength);

	ASGPlayer* SGPlayer = Cast<ASGPlayer>(SGPlayerController->GetPawn());
	if (SGPlayer != nullptr)
	{
		SGPlayer->DisableInput(SGPlayerController);
	}
}

void ASGPortal::SetLoadNextStageTimer(float LoadStageTimer)
{
	GetWorld()->GetTimerManager().SetTimer(LoadStageTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
		SGGameInstance->LoadNextStage();
	}), LoadStageTimer, false);
}

void ASGPortal::Disable()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void ASGPortal::Activate()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	ParticleSystem->Activate(true);
}
