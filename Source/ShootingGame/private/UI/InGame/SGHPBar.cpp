#include "SGHPBar.h"
#include "Components/ProgressBar.h"

void USGHPBar::SetHPProgressBar(float HPRatio)
{
	SGCHECK(HPProgressBar);
	HPProgressBar->SetPercent(HPRatio);
}
