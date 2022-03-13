#pragma once

#include "fmod.hpp"
#include "fmod_studio.hpp"
#include "fmod_common.h"
#include <string>
#include <unordered_map>

class AudioEngine
{
public:
	static int ErrorCheck(FMOD_RESULT result);
	void init();
	void studioinit();
	void update();
	void studioupdate();
	void shutdown();
	void studioshutdown();

	void loadSound(const std::string& soundName, const std::string& filename, bool b3d, bool bLooping = false, bool bStream = false);
	void loadBank(const std::string& filename);
	void unloadSound(const std::string& soundName);
	void unloadBank();
	void playSoundByName(const std::string& soundName);

private:
	FMOD::System* pSystem;
	FMOD::Studio::System* pStudioSystem;
	std::unordered_map<std::string, FMOD::Sound*> sounds;
};

