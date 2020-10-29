#include "SGGameClearWidget.h"

float USGGameClearWidget::PlayFadeAnimation()
{
	PlayAnimation(Fade);
	return Fade->GetEndTime();
}
