#include "SGBossAnimInstance.h"

void USGBossAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();


}

void USGBossAnimInstance::SetDead()
{
	bIsDead = true;
}

//void USGBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
//{
//	Super::NativeUpdateAnimation()
//}
