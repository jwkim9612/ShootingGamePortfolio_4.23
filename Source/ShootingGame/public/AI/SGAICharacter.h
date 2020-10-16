#pragma once

#include "ShootingGame.h"
#include "GameFramework/Character.h"
#include "SGAICharacter.generated.h"

UCLASS()
class SHOOTINGGAME_API ASGAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASGAICharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);

	void DropItem();

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UPawnSensingComponent* PawnSensing;

	UPROPERTY()
	class ASGAIController* SGAIController;

private:
	UPROPERTY(EditAnywhere, category = "Stat", meta = (AllowPrivateAccess = true))
	int32 Health;

	UPROPERTY(EditAnywhere, category = "DropAmmo", meta = (AllowPrivateAccess = true))
	TSubclassOf<class ASGAmmo> DropAmmo;
};
