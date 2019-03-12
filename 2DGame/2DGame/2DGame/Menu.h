#pragma once
#include "Scene.h"
#include "Button.h"

class Menu :
	public Scene
{
public:
	Menu();
	~Menu();

	void init();
	void init(string sprites[], glm::vec2 positions[], int nButtons);
	void update(int deltaTime);
	void render();
	int isButtonPressed();
	void mouseMove(int x, int y, bool bLeft);
	void mouseReleased(int mouseX, int mouseY);

private:
	vector<Button*> buttons;
	Texture colorTexture;
	//ShaderProgram simpleTexProgram;
	float currentTime;
	glm::mat4 projection;

	void initShaders();
	ShaderProgram texProgram;
};

