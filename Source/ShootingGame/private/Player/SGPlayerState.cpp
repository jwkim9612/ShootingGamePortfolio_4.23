#include "SGPlayerState.h"
#include "SGPlayer.h"
#include "SGSaveGame.h"
#include "SGWeapon.h"
#include "SGGameInstance.h"

void ASGPlayerState::InitPlayerData(ASGPlayer* Player)
{
	SGCHECK(Player);
	SGPlayer = Player;

	int32 Health = Player->GetHealth();
	MaxHP = Health;
	CurrentHP = Health;
}

void ASGPlayerState::SetHPToDamage(int32 Damage)
{
	SetHP(FMath::Clamp(CurrentHP - Damage, 0, MaxHP));
}

void ASGPlayerState::SetHP(int32 NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();

	if (CurrentHP <= 0)
	{
		OnHPIsZero.Broadcast();
	}
}

float ASGPlayerState::GetHPRatio() const
{
	float HPRatio = static_cast<float>(CurrentHP) / static_cast<float>(MaxHP);
	return HPRatio;
}

bool ASGPlayerState::IsMaxHP() const
{
	if (CurrentHP == MaxHP)
	{
		return true;
	}
	return false;
}

void ASGPlayerState::HealHP()
{
	SetHP(FMath::Clamp(CurrentHP + 1, 0, MaxHP));
}

void ASGPlayerState::SavePlayerData()
{
	USGGameInstance* SGGameInstance = Cast<USGGameInstance>(GetGameInstance());
	SGCHECK(SGGameInstance);

	USGSaveGame* NewPlayerData = NewObject<USGSaveGame>();
	NewPlayerData->RifleName = SGGameInstance->GetSelectedRifleName();
	NewPlayerData->PistolName = SGGameInstance->GetSelectedPistolName();
	NewPlayerData->RifleAmmo = SGPlayer->GetRifle()->GetAmmo();
	NewPlayerData->RifleMaxAmmo = SGPlayer->GetRifle()->GetMaxAmmo();
	NewPlayerData->PistolAmmo = SGPlayer->GetPistol()->GetAmmo();
	NewPlayerData->PistolMaxAmmo = SGPlayer->GetPistol()->GetMaxAmmo();
	NewPlayerData->Stage = SGGameInstance->GetNextStage();

	if(!UGameplayStatics::SaveGameToSlot(NewPlayerData, TEXT("PlayerSaveData"), 0))
	{
		SGLOG(Warning, TEXT("Error Save!!"));
	}
}
