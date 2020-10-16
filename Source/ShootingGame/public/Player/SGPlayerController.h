#pragma once

#include "ShootingGame.h"
#include "GameFramework/PlayerController.h"
#include "SGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API ASGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASGPlayerController();

public:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void BeginPlay() override;

public:
	class USGHUDWidget* GetSGHUDWidget() const;

	void SetDefaultSpreadCrossHair(float SpreadValue);
	void SetCurrentSpreadCrossHair(float SpreadValue);

private:
	void BindWidgetToPlayerState();

private:
	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowprivateAccess = true))
	TSubclassOf<class UUserWidget> SGHUDWidgetClass;

	UPROPERTY()
	class USGHUDWidget* SGHUDWidget;

	UPROPERTY()
	class ASGPlayerState* SGPlayerState;


};
