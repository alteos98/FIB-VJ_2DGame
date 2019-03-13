#include <iostream>
#include "Scene.h"

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

bool Scene::ButtonPress(int x, int y) {
	if ((x > button->getposB().x + SCREEN_X && x < (button->getposB().x + button->getWidth() + SCREEN_X))
		&& (y > button->getposB().y + SCREEN_Y && y < (button->getposB().y + button->getHeight() + SCREEN_Y))) {
		printf("�GO!");printf("%i, %i \n", x, y);
		return true;
	}
	printf("%i, %i \n", x, y);
	return false;
}



