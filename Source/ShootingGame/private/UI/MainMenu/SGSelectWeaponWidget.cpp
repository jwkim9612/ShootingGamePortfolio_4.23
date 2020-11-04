#include "SGSelectWeaponWidget.h"
#include "SGMainMenuPlayerController.h"
#include "SGWeaponButton.h"
#include "SGGameInstance.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBoxSlot.h"

void USGSelectWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SGMainMenuPlayerController = Cast<ASGMainMenuPlayerController>(GetOwningPlayer());
	SGCHECK(SGMainMenuPlayerController);

	SGGameInstance = Cast<USGGameInstance>(GetGameInstance());
	SGCHECK(SGGameInstance);

	SelectButton->OnClicked.AddUniqueDynamic(this, &USGSelectWeaponWidget::OnSelectClicked);
	BackButton->OnClicked.AddUniqueDynamic(this, &USGSelectWeaponWidget::OnBackClicked);

	HideSelectButton();
	HideSelectedWeaponText();
	CreateWeaponButtonList();
}

void USGSelectWeaponWidget::ShowSelectButton()
{
	SelectButton->SetVisibility(ESlateVisibility::Visible);
}

void USGSelectWeaponWidget::HideSelectButton()
{
	SelectButton->SetVisibility(ESlateVisibility::Collapsed);
}

void USGSelectWeaponWidget::SetSelectedWeaponText(FString WeaponName)
{
	FString StrText = FString::Printf(TEXT("Selected Weapon : %s"), *WeaponName);
	SelectedWeaponText->SetText(FText::FromString(StrText));
}

void USGSelectWeaponWidget::ShowSelectedWeaponText()
{
	SelectedWeaponText->SetVisibility(ESlateVisibility::Visible);
}

void USGSelectWeaponWidget::HideSelectedWeaponText()
{
	SelectedWeaponText->SetVisibility(ESlateVisibility::Collapsed);
}

void USGSelectWeaponWidget::OnSelectClicked()
{
	SGLOG(Warning, TEXT("Base"));
}

void USGSelectWeaponWidget::OnBackClicked()
{
	SGLOG(Warning, TEXT("Base"));
}

void USGSelectWeaponWidget::OnNextClicked()
{
	++CurrentPage;
	UpdatePageButtonsVisibility();
	UpdateWeaponButtons();
}

void USGSelectWeaponWidget::OnPreviousClicked()
{
	--CurrentPage;
	UpdatePageButtonsVisibility();
	UpdateWeaponButtons();
}

void USGSelectWeaponWidget::CreateWeaponButtonList()
{
	// 재생성 방지
	if (WeaponButtonList.Num() == 0)
	{
		// 최대 표시되는 무기 갯수에 맞게 무기버튼 생성.
		for (int WeaponButtonIndex = 0; WeaponButtonIndex < MaxCountOfWeaponSelectButtonPerPage; ++WeaponButtonIndex)
		{
			WeaponButtonList.Emplace(CreateWidget<USGWeaponButton>(this, SGWeaponButton->GetClass()));
		}

		// 원본 숨기기.
		SGWeaponButton->SetVisibility(ESlateVisibility::Collapsed);

		// HorizontalBox의 자식으로 설정
		for (const auto& WeaponButton : WeaponButtonList)
		{
			WeaponButtonBox->AddChild(WeaponButton);
		}

		TArray<UPanelSlot*> PanelSlots = WeaponButtonBox->GetSlots();
		for (const auto& PanelSlot : PanelSlots)
		{
			FSlateChildSize SlateChildSize;

			UHorizontalBoxSlot* HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(PanelSlot);
			HorizontalBoxSlot->SetSize(SlateChildSize);
			HorizontalBoxSlot->SetHorizontalAlignment(HAlign_Center);
			HorizontalBoxSlot->SetVerticalAlignment(VAlign_Center);
		}
	}

	int WeaponNameCount = WeaponNameList.Num();
	if (WeaponNameCount == 0)
	{
		SGLOG(Warning, TEXT("Please enter weapon name"));
		return;
	}

	PageCount = FMath::Clamp(WeaponNameCount - MaxCountOfWeaponSelectButtonPerPage + 1, 1, WeaponNameCount - MaxCountOfWeaponSelectButtonPerPage + 1);
	CurrentPage = 1;

	//한 페이지의 최대 버튼 수 보다 같거나 작을 때
	//if (WeaponNameCount <= UIService::MaxCountOfWeaponSelectButtonPerPage)
	if (PageCount == 1)
	{
		// 나머지 버튼 숨기기.
		for (int WeaponButtonIndex = WeaponNameCount; WeaponButtonIndex < MaxCountOfWeaponSelectButtonPerPage; ++WeaponButtonIndex)
		{
			WeaponButtonList[WeaponButtonIndex]->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	else
	{
		NextButton->OnClicked.Clear(); 
		PreviousButton->OnClicked.Clear();
		NextButton->OnClicked.AddDynamic(this, &USGSelectWeaponWidget::OnNextClicked);
		PreviousButton->OnClicked.AddDynamic(this, &USGSelectWeaponWidget::OnPreviousClicked);
	}

	UpdatePageButtonsVisibility();
	UpdateWeaponButtons();
}

void USGSelectWeaponWidget::UpdatePageButtonsVisibility()
{
	if (PageCount == 1)
	{
		NextButton->SetVisibility(ESlateVisibility::Collapsed);
		PreviousButton->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	if (CurrentPage == 1)
	{
		NextButton->SetVisibility(ESlateVisibility::Visible);
		PreviousButton->SetVisibility(ESlateVisibility::Collapsed);
	}
	else if (CurrentPage == PageCount)
	{
		NextButton->SetVisibility(ESlateVisibility::Collapsed);
		PreviousButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		NextButton->SetVisibility(ESlateVisibility::Visible);
		PreviousButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void USGSelectWeaponWidget::UpdateWeaponButtons()
{
	
}
