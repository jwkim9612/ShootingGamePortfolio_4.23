#include "SGCrossHair.h"
#include "Components/VerticalBox.h"

void USGCrossHair::NativeConstruct()
{
	Super::NativeConstruct();

	SetCurrentSpreadValue(20.0f);
	SetDefaultSpreadValue(20.0f);
}

void USGCrossHair::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CurrentSpreadValue != DefaultSpreadValue)
	{
		CurrentSpreadValue = FMath::FInterpTo(CurrentSpreadValue, DefaultSpreadValue, InDeltaTime, 3.0f);
		SpreadCrossHair(CurrentSpreadValue);
	}
}

void USGCrossHair::SetDefaultSpreadValue(float NewSpreadValue)
{
	DefaultSpreadValue = NewSpreadValue;
}

void USGCrossHair::SetCurrentSpreadValue(float NewSpreadValue)
{
	CurrentSpreadValue = NewSpreadValue;
}

float USGCrossHair::GetSpreadValue() const
{
	return CurrentSpreadValue;
}

void USGCrossHair::SpreadCrossHair(float NewSpreadValue)
{
	Top->SetRenderTranslation(FVector2D(0.0f, -NewSpreadValue));
	Down->SetRenderTranslation(FVector2D(0.0f, NewSpreadValue));
	Left->SetRenderTranslation(FVector2D(-NewSpreadValue, 0.0f));
	Right->SetRenderTranslation(FVector2D(NewSpreadValue, 0.0f));
}
