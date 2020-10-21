#include "SGFootStepSoundList.h"
#include "Sound/SoundCue.h"

USoundCue* USGFootStepSoundList::GetSound(FString SoundName)
{
	USoundCue** Sound = SoundList.Find(SoundName);
	if (Sound != nullptr)
	{
		return *Sound;
	}

	return nullptr;
}
