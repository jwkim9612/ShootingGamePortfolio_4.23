#include "SGHitEffect.h"

void USGHitEffect::PlayFadeAnimation()
{
	SGCHECK(Fade);
	
	PlayAnimation(Fade);
}
