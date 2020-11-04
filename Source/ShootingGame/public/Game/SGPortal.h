#pragma once

#include "ShootingGame.h"
#include "GameFramework/Actor.h"
#include "SGPortal.generated.h"

UCLASS()
class SHOOTINGGAME_API ASGPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	ASGPortal();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void SetLoadNextStageTimer(float LoadStageTimer);

public:
	UFUNCTION()
	void Activate();
	void Disable();

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ParticleSystem;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UCapsuleComponent* CapsuleComponent;

private:
	UPROPERTY()
	class USGGameInstance* SGGameInstance;

	UPROPERTY()
	class ASGPlayerController* SGPlayerController;

	UPROPERTY()
	class USGHUDWidget* SGHUDWidget;

private:
	FTimerHandle LoadStageTimerHandle;

	bool bIsPlayerEntered;
};
