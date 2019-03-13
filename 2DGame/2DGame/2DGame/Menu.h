#pragma once
#include "Button.h"

class Menu
{
public:
	Menu();
	~Menu();

	void init();
	void loadMenu(string sprites[], glm::vec2 positions[], glm::ivec2 sizeButtons[], glm::vec2 relation[], int nButtons);
	void update(int deltaTime);
	void render();
	int ButtonPress(int x, int y);

private:
	vector<Button*> buttons;
	Texture colorTexture;
	float currentTime;
	glm::mat4 projection;

	void initShaders();
	ShaderProgram texProgram;
};

