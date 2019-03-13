#include "Menu.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"

Menu::Menu()
{
}


Menu::~Menu()
{
}

void Menu::init() {}

void Menu::loadMenu(string sprites[], glm::vec2 positions[], int nButtons)
{
	/*initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;*/
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	initShaders();

	/*backgroundQuad = MaskedTexturedQuad::createTexturedQuad(geom, texCoords, simpleTexProgram);
	colorTexture.loadFromFile(background, TEXTURE_PIXEL_FORMAT_RGBA);
	colorTexture.setMinFilter(GL_NEAREST);
	colorTexture.setMagFilter(GL_NEAREST);*/

	for (int i = 0; i < nButtons; i++) {
		Button *b = new Button;
		b->init(positions[i], sprites[i], texProgram);
		buttons.push_back(b);
	}
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
}

void Menu::update(int deltaTime)
{
	
}

void Menu::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->render();
}

void Menu::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

int Menu::isButtonPressed()
{
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons[i]->isSelected())
			return i;
	}
	return -1;
}

void Menu::mouseMove(int x, int y, bool bLeft) {
	for (int i = 0; i < buttons.size(); ++i) {
		buttons[i]->mouseMoved(x, y, bLeft);
	}
}

void Menu::mouseReleased(int mouseX, int mouseY) {
	int buttonSelected = isButtonPressed();
	for (int i = 0; i < buttons.size(); i++) {
		if (!(buttons[i]->mouseReleased(mouseX, mouseY))) {
			buttons[i]->mouseMoved(mouseX, mouseY, false);
			if (buttons[i]->isSelected())
				if (buttonSelected != -1 && buttonSelected != i)
					buttons[buttonSelected]->deselect();
		}
	}
}