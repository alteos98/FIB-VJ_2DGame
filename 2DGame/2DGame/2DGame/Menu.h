#pragma once
#include "Button.h"
#include "AudioEngine.h"

class Menu
{
public:
	Menu();
	~Menu();

	void init();
	void loadMenu(
		string sprites[],
		glm::vec2 positions[],
		glm::ivec2 sizeButtons[],
		glm::vec2 relation[],
		int nButtons,
		bool clear
	);
	void update(int deltaTime);
	void render();
	int buttonPress(int x, int y);
	void addBackground(string background, int nFrames);
	void addImage(string nameImage, glm::vec2 quadSize, glm::vec2 sizeInSpritesheet, glm::vec2 position);
	void loadMusicAndSoundEffects();
	void free();

private:
	vector<Button*> buttons;

	bool hasBackground;
	vector<Sprite*> background;
	Texture texture1, texture2;

	vector<Sprite*> images;

	float currentTime;
	glm::mat4 projection;

	void initShaders();
	ShaderProgram texProgram;
};

