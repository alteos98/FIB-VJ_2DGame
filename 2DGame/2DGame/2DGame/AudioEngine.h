#pragma once
#include <SDL_mixer.h>
#include <map>
#include <iostream>
#include <string>


	class SoundEffect {
	public:
		friend class AudioEngine;
		void play(int loops = 0);
	private:
		Mix_Chunk* m_chunk = nullptr;
	};

	class Music {
	public:
		friend class AudioEngine;
		void play(int loops = 1);

		static void pause();
		static void stop();
		static void resume();

	private:
		Mix_Music* m_music = nullptr;
	};

	class AudioEngine {
	public:
		AudioEngine();
		~AudioEngine();

		std::string dirmusica;
		std::string dirsonido;

		static AudioEngine &instance() {
			static AudioEngine ae;
			
			return ae;
		}

		void init();
		void destroy();

		SoundEffect loadSoundEffect(const std::string& filePath);
		Music loadMusic(const std::string& filePath);

		std::map<std::string, SoundEffect> sonidos;
		std::map<std::string, Music> musicas;

	private:
		std::map<std::string, Mix_Chunk*> m_effectMap;
		std::map <std::string, Mix_Music*> m_musicMap;
		bool isinizialized = false;

	};