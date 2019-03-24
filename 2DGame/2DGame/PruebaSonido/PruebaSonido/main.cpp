#include <iostream>
#include "AudioEngine.h"



void main(int argc, char **argv) {
	AudioEngine m_audioEngine = AudioEngine();

	m_audioEngine.init();

	SoundEffect soundeffect, soundeffect2;

	soundeffect = m_audioEngine.loadSoundEffect("C:/Users/alber/Documents/FMOD Studio/examples/Assets/VO/English/vo_en_welcome.ogg");

	//Music music = m_audioEngine.loadMusic("C:/Users/alber/Documents/GitHub/FIB-VJ_2DGame/2DGame/2DGame/PruebaSonido/Music/Titeknots.ogg");
	//music.play(-1);
	soundeffect.play(100);

	//soundeffect2 = m_audioEngine.loadSoundEffect("C:/Users/alber/Documents/FMOD Studio/examples/Assets/Character/Radio/placeholder_640166_main_meco.ogg");
	//soundeffect2.play(1);


	while (1);
}