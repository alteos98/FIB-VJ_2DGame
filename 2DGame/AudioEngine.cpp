#include "AudioEngine.h"

	void SoundEffect::play(int loops) {
		if (Mix_PlayChannel(-1, m_chunk, loops) == -1) {
			std::cout << "ERROR MIX_PLAYCHANNEL";
			int a;
			std::cin >> a;
			exit(69);
		}
	}

	void Music::play(int loops) {
		if (Mix_PlayMusic(m_music, loops) == -1) {
			std::cout << "ERROR MIX_PLAYMUSIC";
			int a;
			std::cin >> a;
			exit(69);
		}
	}

	void Music::pause(){
		Mix_PauseMusic();
	}
	void Music::stop(){
		Mix_HaltMusic();
	}
	void Music::resume(){
		Mix_ResumeMusic();
	}

	AudioEngine::AudioEngine(){}

	AudioEngine::~AudioEngine(){
		destroy();
	}

	void AudioEngine::init() {
		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
			std::cout << "ERROR MIX_INIT";
			int a;
			std::cin >> a;
			exit(69);
		}
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
			std::cout << "ERROR MIX_OPENAUDIO";
			int a;
			std::cin >> a;
			exit(69);
		}
		isinizialized = true;
	}

	void AudioEngine::destroy(){
		if (isinizialized) {
			isinizialized = false;
			Mix_Quit();
		}
	}

	SoundEffect AudioEngine::loadSoundEffect(const std::string& filePath){
		auto it = m_effectMap.find(filePath);
		SoundEffect effect;

		if (it == m_effectMap.end()) {
			Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
			if (chunk == nullptr) {
				std::cout << "ERROR MIX_LOADWAV" << std::string(Mix_GetError()) << '1';
				int a;
				std::cin >> a;
				exit(69);
			}

			effect.m_chunk = chunk;
			m_effectMap[filePath] = chunk;
		}
		else {
			effect.m_chunk = it->second;
		}
		return effect;
	}

	/*
	Music AudioEngine::loadMusic(const std::string& filePath){
		auto it = m_musicMap.find(filePath);
		Music music;

		if (it == m_musicMap.end()) {
			Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
			if (mixMusic == nullptr) {
				std::cout << "ERROR MIX_LOADMUS  -- " << std::string(Mix_GetError());
				int a;
				std::cin >> a;
				exit(69);
			}

			music.m_music = mixMusic;
			m_musicMap[filePath] = mixMusic;
		}
		else {
			music.m_music = it->second;
		}
		return music;
	}
	*/
