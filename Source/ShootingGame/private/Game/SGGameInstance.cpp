#include "SGGameInstance.h"
#include "SGLoadingScreen.h"
#include "SGFloatingDamageTextPool.h"
#include "StageService.h"
#include "SGSaveGame.h"
#include "SGWeapon.h"

void USGGameInstance::Init()
{
	Super::Init();

	InitializeParticleDataTable();
	InitializeWeaponDataTable();
	InitializeImageDataTable();
	InitializeStageDataTable();

	SGLoadingScreen = CreateWidget<USGLoadingScreen>(this, LoadingScreenClass);
	LoadingTImer = 2.0f;
	CurrentStage = 1;
}

void USGGameInstance::SetSelectedRifleName(FString RifleName)
{
	SelectedRifleName = RifleName;
}

void USGGameInstance::SetSelectedPistolName(FString PistolName)
{
	SelectedPistolName = PistolName;
}

FString USGGameInstance::GetSelectedRifleName() const
{
	return SelectedRifleName;
}

FString USGGameInstance::GetSelectedPistolName() const
{
	return SelectedPistolName;
}

FString USGGameInstance::GetRandomWeaponName() const
{
	int32 WeaponCount = WeaponNames.Num();
	int32 RandomIndex = FMath::RandRange(0, WeaponCount -1);

	return WeaponNames[RandomIndex];
}

void USGGameInstance::SetCurrentStage(int32 NewStage)
{
	if (NewStage > StageService::FinalStage)
	{
		return;
	}

	CurrentStage = NewStage;
}

int32 USGGameInstance::GetCurrentStage() const
{
	return CurrentStage;
}

int32 USGGameInstance::GetNextStage()
{
	return FMath::Clamp(CurrentStage + 1, 1, StageService::FinalStage);
}

void USGGameInstance::IncreaseStage()
{
	SetCurrentStage(FMath::Clamp(CurrentStage + 1, 1, StageService::FinalStage));
}

USGSaveGame * USGGameInstance::GetSaveData() const
{
	USGSaveGame* SGSaveGame = Cast<USGSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerSaveData"), 0));
	return SGSaveGame;
}

void USGGameInstance::DeleteSaveData()
{
	UGameplayStatics::DeleteGameInSlot(TEXT("PlayerSaveData"), 0);
}

void USGGameInstance::InitializeParticleDataTable()
{
	SGCHECK(ParticleDataTable);

	TArray<FName> Names = ParticleDataTable->GetRowNames();
	ParticleTable.Reserve(Names.Num());
	for (const FName& Name : Names)
	{
		FSGParticleData* Data = ParticleDataTable->FindRow<FSGParticleData>(Name, TEXT(""));
		if (!Data->ParticlePath.IsNull())
		{
			ParticleTable.Emplace(Data->Name, AssetLoader.LoadSynchronous(Data->ParticlePath));
		}
	}
}

void USGGameInstance::InitializeWeaponDataTable()
{
	SGCHECK(WeaponDataTable);

	TArray<FName> Names = WeaponDataTable->GetRowNames();
	WeaponTable.Reserve(Names.Num());
	WeaponNames.Reserve(Names.Num());
	for (const FName& Name : Names)
	{
		FSGWeaponData* Data = WeaponDataTable->FindRow<FSGWeaponData>(Name, TEXT(""));
		if (Data->Class != nullptr)
		{
			ASGWeapon* Weapon = Data->Class->GetDefaultObject<ASGWeapon>();
			Weapon->SetWeaponData(Data);
			WeaponTable.Emplace(Data->Name, *Data);
			WeaponNames.Emplace(Data->Name);
		}
	}
}

void USGGameInstance::InitializeImageDataTable()
{
	SGCHECK(ImageDataTable);

	TArray<FName> Names = ImageDataTable->GetRowNames();
	ImageTable.Reserve(Names.Num());
	for (const FName& Name : Names)
	{
		FSGImageData* Data = ImageDataTable->FindRow<FSGImageData>(Name, TEXT(""));
		if (!Data->ImagePath.IsNull())
		{
			ImageTable.Emplace(Data->Name, AssetLoader.LoadSynchronous(Data->ImagePath));
		}
	}
}

void USGGameInstance::InitializeStageDataTable()
{
	SGCHECK(StageDataTable);

	TArray<FName> Names = StageDataTable->GetRowNames();
	StageTable.Reserve(Names.Num());
	for (const FName& Name : Names)
	{
		FSGStageData* Data = StageDataTable->FindRow<FSGStageData>(Name, TEXT(""));
		if (Data->Id != 0)
		{
			StageTable.Emplace(Data->Id, *Data);
		}
	}
}

void USGGameInstance::CreateFloatingDamageTextPool()
{
	FloatingDamageTextPool = GetWorld()->SpawnActor<ASGFloatingDamageTextPool>(FloatingDamageTextPoolClass, FVector::ZeroVector, FRotator::ZeroRotator);
}

UParticleSystem * USGGameInstance::TryGetParticleSystem(FString Name)
{
	if (UParticleSystem** ParticleSystem = ParticleTable.Find(Name))
	{
		return *ParticleSystem;
	}

	SGLOG(Warning, TEXT("%s is no Data"), *Name)
		return nullptr;
}

FSGWeaponData* USGGameInstance::TryGetWeaponData(FString Name)
{
	if (FSGWeaponData* Data = WeaponTable.Find(Name))
	{
		return Data;
	}

	SGLOG(Warning, TEXT("%s is no Data"), *Name);
	return nullptr;
}

FSGWeaponData * USGGameInstance::GetRandomWeaponData()
{
	return TryGetWeaponData(GetRandomWeaponName());
}

UTexture2D* USGGameInstance::TryGetImage(FString Name)
{
	if (UTexture2D** Image = ImageTable.Find(Name))
	{
		return *Image;
	}

	SGLOG(Warning, TEXT("%s is no Data"), *Name);
	return nullptr;
}

FSGStageData * USGGameInstance::TryGetStageData(int32 Id)
{
	if (FSGStageData* Data = StageTable.Find(Id))
	{
		return Data;
	}

	SGLOG(Warning, TEXT("ID %d is no Data"), Id);
	return nullptr;
}

void USGGameInstance::PlayFloatingDamageText(int32 Damage, FVector Location, bool bIsHitHead)
{
	FloatingDamageTextPool->SetTextAndPlay(Damage, Location, bIsHitHead);
}

void USGGameInstance::LoadNextStage()
{
	IncreaseStage();
	LoadStage();
}

void USGGameInstance::LoadStage()
{
	FSGStageData* Data = TryGetStageData(CurrentStage);

	SGLoadingScreen->SetData(Data);
	SGLoadingScreen->AddToViewport();

	GetWorld()->GetTimerManager().SetTimer(LoadingTimerHandle, FTimerDelegate::CreateLambda([this, Data]() -> void {
		UGameplayStatics::OpenLevel(this, FName(*Data->Name));
	}), LoadingTImer, false);
}

void USGGameInstance::LoadMainMenu()
{
	UGameplayStatics::OpenLevel(this, TEXT("MainMenu"));
}
