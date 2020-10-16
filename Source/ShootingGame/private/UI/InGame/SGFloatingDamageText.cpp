#include "SGFloatingDamageText.h"
#include "Components/TextBlock.h"

void USGFloatingDamageText::SetText(FString NewDamageText, bool bIsHitHead)
{
	DamageText->SetText(FText::FromString(NewDamageText));

	if (bIsHitHead)
	{
		DamageText->SetColorAndOpacity(FSlateColor(FLinearColor(255.0f / 255.0f, 69.0f / 255.0f , 0.0f))); // orange red
	}
	else
	{
		DamageText->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	}
}

void USGFloatingDamageText::PlayFadeAnimation()
{
	PlayAnimation(Fade);
}
