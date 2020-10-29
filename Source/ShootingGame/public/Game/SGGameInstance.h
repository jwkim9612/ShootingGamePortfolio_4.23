#pragma once

#include "ShootingGame.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Engine/StreamableManager.h"
#include "SGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API USGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	void Init() override;

public:
	void SetSelectedRifleName(FString RifleName);
	void SetSelectedPistolName(FString PistolName);
	FString GetSelectedRifleName() const;
	FString GetSelectedPistolName() const;
	FString GetRandomWeaponName() const;

	void SetCurrentStage(int32 NewStage);
	int32 GetCurrentStage() const;
	int32 GetNextStage();
	void IncreaseStage();

private:
	void InitializeParticleDataTable();
	void InitializeWeaponDataTable();
	void InitializeImageDataTable();
	void InitializeStageDataTable();

public:
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void CreateFloatingDamageTextPool();

public:
	class UParticleSystem* TryGetParticleSystem(FString Name);
	struct FSGWeaponData* TryGetWeaponData(FString Name);
	struct FSGWeaponData* GetRandomWeaponData();
	class UTexture2D* TryGetImage(FString Name);
	struct FSGStageData* TryGetStageData(int32 Id);

	void PlayFloatingDamageText(int32 Damage, FVector Location, bool bIsHitHead = false);
	void LoadNextStage();
	void LoadStage();
	void LoadMainMenu();

public:
	FStreamableManager AssetLoader;

private:
	UPROPERTY(EditAnywhere, Category = "ParticleDataTable")
	class UDataTable* ParticleDataTable;

	UPROPERTY(EditAnywhere, Category = "WeaponDataTable")
	class UDataTable* WeaponDataTable;

	UPROPERTY(EditAnywhere, Category = "ImageDataTable")
	class UDataTable* ImageDataTable;

	UPROPERTY(EditAnywhere, Category = "StageDataTable")
	class UDataTable* StageDataTable;

private:
	UPROPERTY()
	TMap<FString, class UParticleSystem*> ParticleTable;

	UPROPERTY()
	TMap<FString, class UTexture2D*> ImageTable;

	TMap<FString, struct FSGWeaponData> WeaponTable;
	TMap<int32, struct FSGStageData> StageTable;

	UPROPERTY()
	TArray<FString> WeaponNames;

private:
	UPROPERTY(EditAnywhere, Category = "FloatingDamageText")
	TSubclassOf<class ASGFloatingDamageTextPool> FloatingDamageTextPoolClass;

	UPROPERTY()
	class ASGFloatingDamageTextPool* FloatingDamageTextPool;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Loading")
	TSubclassOf<class USGLoadingScreen> LoadingScreenClass;

	UPROPERTY()
	class USGLoadingScreen* SGLoadingScreen;

	FTimerHandle LoadingTimerHandle;
	float LoadingTImer;

private:
	int32 CurrentStage;

private:
	FString SelectedRifleName;
	FString SelectedPistolName;
};
