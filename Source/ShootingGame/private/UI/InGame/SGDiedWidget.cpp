#include "SGDiedWidget.h"

float USGDiedWidget::PlayFadeAnimation()
{
	PlayAnimation(Fade);
	return Fade->GetEndTime();
}
