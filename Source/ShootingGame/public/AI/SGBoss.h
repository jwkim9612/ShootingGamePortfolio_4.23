#pragma once

#include "ShootingGame.h"
#include "GameFramework/Character.h"
#include "SGBoss.generated.h"

UCLASS()
class SHOOTINGGAME_API ASGBoss : public ACharacter
{
	GENERATED_BODY()

public:
	ASGBoss();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
