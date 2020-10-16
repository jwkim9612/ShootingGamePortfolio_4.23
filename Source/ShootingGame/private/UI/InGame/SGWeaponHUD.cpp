#include "SGWeaponHUD.h"
#include "SGWeapon.h"
#include "SGPlayer.h"
#include "SGGameInstance.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USGWeaponHUD::UpdateAmmo()
{
	SGCHECK(CurrentWeapon);

	Ammo->SetText(FText::FromString(FString::FromInt(CurrentWeapon->GetAmmo())));
	MaxAmmo->SetText(FText::FromString(FString::FromInt(CurrentWeapon->GetMaxAmmo())));
}

void USGWeaponHUD::UpdateWeapon()
{
	SGCHECK(CurrentWeapon);

	FString WeaponName = StaticEnum<WeaponType>()->GetNameStringByValue(static_cast<int64>(CurrentWeapon->GetWeaponType()));
	Name->SetText(FText::FromString(WeaponName));

	auto GameInstance = Cast<USGGameInstance>(GetWorld()->GetGameInstance());
	Image->SetBrushFromTexture(GameInstance->TryGetImage(WeaponName));
}

void USGWeaponHUD::SetCurrentWeapon(class ASGWeapon* NewWeapon)
{
	SGCHECK(NewWeapon);
	CurrentWeapon = NewWeapon;
}

void USGWeaponHUD::BindPlayer(class ASGPlayer* NewPlayer)
{
	SGCHECK(NewPlayer);

	NewPlayer->OnWeaponChanged.AddDynamic(this, &USGWeaponHUD::UpdateAmmo);
	NewPlayer->OnWeaponChanged.AddDynamic(this, &USGWeaponHUD::UpdateWeapon);
}

void USGWeaponHUD::BindWeapon(ASGWeapon * NewWeapon)
{
	SGCHECK(NewWeapon);

	NewWeapon->OnAmmoChanged.AddDynamic(this, &USGWeaponHUD::UpdateAmmo);
}
