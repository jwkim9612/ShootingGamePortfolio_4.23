#pragma once

#include "ShootingGame.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "SGAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API ASGAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASGAIController();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

public:
	void SetTargetKey(AActor* Actor);
	void SetDetectedKey(bool bDetected);

private:
	UPROPERTY()
	class ASGAICharacter* SGAICharacter;

	UPROPERTY()
	class UBlackboardData* BlackBoardData;

	UPROPERTY()
	class UBehaviorTree* BehaviorTree;

	UPROPERTY()
	class UAISenseConfig_Sight* AISightConfig;

public:
	static const FName bDetectedKey;
	static const FName OriginLocationKey;
	static const FName PatrolLocationKey;
	static const FName TargetKey;
};
