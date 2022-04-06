#include "AudioEngine.h"
#include "fmod_errors.h"
#include "fmod_studio_common.h"
#include "fmod_studio.hpp"
#include <iostream>
#include "ToneFire.h"
#include "fmod_studio_common.h"

ToneFire::FMODStudio AudioEngine::studio;
ToneFire::StudioSound AudioEngine::audio;


int AudioEngine::ErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK) 
	{
		std::cout << "FMOD ERROR:" << FMOD_ErrorString(result) << std::endl;

#ifdef _DEBUG
		__debugbreak();
#endif // _DEBUG
		return 1;
	}
	return 0;
}


void AudioEngine::studioinit()
{
	
	return;
}


void AudioEngine::studioupdate()
{
	studio.Update();
}

void AudioEngine::shutdown()
{
	ErrorCheck(pSystem->close());
	ErrorCheck(pSystem->release());
}



void AudioEngine::loadSound(const std::string& soundName, const std::string& filename, bool b3d, bool bLooping, bool bStream)
{
	//checks if already loaded
	auto foundElement = sounds.find(soundName);
	if (foundElement != sounds.end())
	{
		return;
	}

	FMOD_MODE mode = FMOD_DEFAULT;
	mode |= (b3d) ? FMOD_3D : FMOD_2D;
	mode |= (bLooping) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	mode |= (bStream) ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

	FMOD::Sound* LoadedSound;
	ErrorCheck(pSystem->createSound(filename.c_str(), mode, nullptr, &LoadedSound));
	
	if (LoadedSound != nullptr)
	{
		sounds[soundName] = LoadedSound;
	}
}

void AudioEngine::loadBankS()
{
	studio.LoadBank("Master.bank");
	studio.LoadBank("Master.strings.bank");
	studio.LoadBank("Music.bank");
	studio.LoadBank("SoundEffects.bank");
	studio.LoadBank("Dialog.bank");

}

//FMOD_RESULT AudioEngine::s(const char* filename, FMOD::Studio::Bank** bank = NULL)
//{
//	return pStudioSystem->loadBankFile(filename, FMOD_STUDIO_LOAD_BANK_NORMAL, bank);
//}



void AudioEngine::unloadSound(const std::string& soundName)
{
	auto foundElement = sounds.find(soundName);
	if (foundElement != sounds.end())
	{
		ErrorCheck(foundElement->second->release());
		sounds.erase(foundElement);
	}
}

void AudioEngine::loadEventS()
{
	audio.LoadEvent("event:/Sounds/Music/Loading/LoadingMusicEvent");
	audio.LoadEvent("event:/Sounds/Music/Lose/LoseMusicEvent");
	audio.LoadEvent("event:/Sounds/Music/Main/MainMusicEvent");
	audio.LoadEvent("event:/Sounds/Music/Menu/MenuMusicEvent");
	audio.LoadEvent("event:/Sounds/Music/Tutorial/TutorialMusicEvent");
	audio.LoadEvent("event:/Sounds/Music/Victory/VictoryMusicEvent");
	audio.LoadEvent("event:/Sounds/SoundEffects/Footstep");
	audio.LoadEvent("event:/Sounds/SoundEffects/Pickups interactions/DepositTrash");
	audio.LoadEvent("event:/Sounds/SoundEffects/Pickups interactions/PickUpCup");
	audio.LoadEvent("event:/Sounds/SoundEffects/Pickups interactions/PickUpTrash");
	audio.LoadEvent("event:/Sounds/SoundEffects/Pickups interactions/TrashPickupStopped");
	audio.LoadEvent("event:/Sounds/SoundEffects/Pickups interactions/TrashyFull");
	audio.LoadEvent("event:/Sounds/SoundEffects/VoiceLines Big Ben/Voice1 (Intro)");
	audio.LoadEvent("event:/Sounds/SoundEffects/VoiceLines Big Ben/Voice2 (Youre a natural)");
	audio.LoadEvent("event:/Sounds/SoundEffects/VoiceLines Big Ben/Voice3 (Remember blue)");
	audio.LoadEvent("event:/Sounds/SoundEffects/VoiceLines Big Ben/Voice4 (Bothering)");
	audio.LoadEvent("event:/Sounds/SoundEffects/VoiceLines Big Ben/Voice5 (Stuck)"); 
}



void AudioEngine::playEventS(const std::string& eventname)
{
	audio.PlayEvent(eventname);
}

void AudioEngine::stopEventS(const std::string& eventname)
{
	audio.StopEvent(eventname);
}

void AudioEngine::EventPosChangeS(const std::string& eventname, float x, float y, float z)
{
	audio.SetEventPosition(eventname, FMOD_VECTOR{ x, y, z });
}

void AudioEngine::EventParamChangeS(const std::string& eventname, std::string& paramname, float x, float y)
{
	audio.SetEventParameter(eventname, paramname, x);
}





void AudioEngine::playSoundByName(const std::string& soundName)
{
	pSystem->playSound(sounds[soundName], nullptr, false, nullptr);
}
