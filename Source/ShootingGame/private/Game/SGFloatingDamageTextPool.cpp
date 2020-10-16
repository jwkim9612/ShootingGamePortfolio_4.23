#include "SGFloatingDamageTextPool.h"
#include "SGFloatingDamageText.h"
#include "PoolService.h"
#include "Components/WidgetComponent.h"

ASGFloatingDamageTextPool::ASGFloatingDamageTextPool()
{
	CreateFloatingDamageTextComponentPool();

	CurrentIndex = 0;
}

void ASGFloatingDamageTextPool::BeginPlay()
{
	Super::BeginPlay();
	
	CreateFloatingDamageTextWidgetPool();
}

void ASGFloatingDamageTextPool::SetTextAndPlay(int32 Damage, FVector Location, bool bIsHitHead)
{
	if (CurrentIndex == PoolService::FloatingDamageTextCount)
	{
		CurrentIndex = 0;
	}

	UWidgetComponent* FloatingDamageTextComponent = FloatingDamageTextComponentPool[CurrentIndex];
	FloatingDamageTextComponent->SetWorldLocation(Location);
	FloatingDamageTextComponent->SetVisibility(true);

	USGFloatingDamageText* FloatingDamageTextWidget = FloatingDamageTextWidgetPool[CurrentIndex];
	FloatingDamageTextWidget->SetText(FString::FromInt(Damage), bIsHitHead);
	FloatingDamageTextWidget->PlayFadeAnimation();

	++CurrentIndex;
}

void ASGFloatingDamageTextPool::CreateFloatingDamageTextComponentPool()
{
	FloatingDamageTextComponentPool.Reserve(PoolService::FloatingDamageTextCount);
	for (int32 i = 0; i < PoolService::FloatingDamageTextCount; i++)
	{
		FString Text = FString(TEXT("FloatingDamageTextWidget"));
		FString Number = FString::FromInt(i);
		Text.Append(Number);

		UWidgetComponent* FloatingTextWidget = CreateDefaultSubobject<UWidgetComponent>(FName(*Text));
		FloatingTextWidget->SetWidgetSpace(EWidgetSpace::Screen);
		FloatingDamageTextComponentPool.Add(FloatingTextWidget);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> FloatingDamageTextWidgetClass(TEXT("/Game/BluePrint/UI/InGame/BP_FloatingDamageText.BP_FloatingDamageText_C"));
	if (FloatingDamageTextWidgetClass.Succeeded())
	{
		for (auto& FloatingDamageTextComponent : FloatingDamageTextComponentPool)
		{
			FloatingDamageTextComponent->SetWidgetClass(FloatingDamageTextWidgetClass.Class);
			FloatingDamageTextComponent->SetDrawSize(FVector2D(50.0f, 5.0f));
		}
	}
}

void ASGFloatingDamageTextPool::CreateFloatingDamageTextWidgetPool()
{
	FloatingDamageTextWidgetPool.Reserve(FloatingDamageTextComponentPool.Num());
	for (const auto& FloatingDamageTextComponent : FloatingDamageTextComponentPool)
	{
		USGFloatingDamageText* SGFloatingDamageText = Cast<USGFloatingDamageText>(FloatingDamageTextComponent->GetUserWidgetObject());
		SGCHECK(SGFloatingDamageText);
		FloatingDamageTextWidgetPool.Add(SGFloatingDamageText);
	}

	for (auto& FloatingDamageTextComponent : FloatingDamageTextComponentPool)
	{
		FloatingDamageTextComponent->SetVisibility(false);
	}
}
