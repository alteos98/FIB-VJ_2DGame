#include "Menu.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"

#define SCREEN_X 0
#define SCREEN_Y 0

Menu::Menu()
{
	for (unsigned int i = 0; i < buttons.size(); ++i) {
		buttons[i] = NULL;
	}
	for (unsigned int i = 0; i < images.size(); ++i) {
		images[i] = NULL;
	}
	background = NULL;
}


Menu::~Menu()
{
	for (unsigned int i = 0; i < buttons.size(); ++i) {
		if (buttons[i] != NULL)
			delete buttons[i];
	}
	for (unsigned int i = 0; i < images.size(); ++i) {
		if (images[i] != NULL)
			delete images[i];
	}
	if (background != NULL)
		delete background;
}

void Menu::init() {}

void Menu::loadMenu(
	string sprites[],
	glm::vec2 positions[],
	glm::ivec2 sizeButtons[],
	glm::vec2 relation[],
	int nButtons,
	bool clear
)
{
	if (clear)
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	buttons.clear();
	images.clear();

	initShaders();
	hasBackground = false;

	for (int i = 0; i < nButtons; i++) {
		Button* b = new Button;
		b->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, sizeButtons[i], relation[i], sprites[i]);
		b->setPosition(positions[i]);
		buttons.push_back(b);
	}
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
}

void Menu::update(int deltaTime)
{
	if (hasBackground)
		background->update(deltaTime);
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

	if (hasBackground)
		background->render();

	for (unsigned int i = 0; i < images.size(); i++)
		images[i]->render();

	for (unsigned int i = 0; i < buttons.size(); i++)
		buttons[i]->render();
}

void Menu::addBackground(string background, int nFrames) {
	hasBackground = true;
	texture1.loadFromFile(background, TEXTURE_PIXEL_FORMAT_RGBA);
	texture1.setMinFilter(GL_NEAREST);
	texture1.setMagFilter(GL_NEAREST);
	glm::vec2 quadSize = glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	glm::vec2 sizeInSpritesheet = glm::vec2(1.f, 1.f / float(nFrames));
	this->background = Sprite::createSprite(quadSize, sizeInSpritesheet, &texture1, &texProgram);
	
	this->background->setNumberAnimations(nFrames);
	this->background->setAnimationSpeed(0, 8);
	for (int i = 0; i < nFrames; ++i)
		this->background->addKeyframe(0, glm::vec2(0.f, float(i) / float(nFrames)));
	this->background->changeAnimation(0);
	this->background->setPosition(glm::vec2(0, 0));
}

void Menu::addImage(string nameImage, glm::vec2 quadSize, glm::vec2 sizeInSpritesheet, glm::vec2 position) {
	texture2.loadFromFile(nameImage, TEXTURE_PIXEL_FORMAT_RGBA);
	texture2.setMinFilter(GL_NEAREST);
	texture2.setMagFilter(GL_NEAREST);
	glm::vec2 _quadSize = quadSize;
	glm::vec2 _sizeInSpritesheet = sizeInSpritesheet;
	Sprite* image = Sprite::createSprite(quadSize, sizeInSpritesheet, &texture2, &texProgram);
	image->setPosition(position);
	images.push_back(image);
}

void Menu::free() {
	background->free();
	for (unsigned int i = 0; i < images.size(); ++i)
		images[i]->free();
	for (unsigned int i = 0; i < buttons.size(); ++i)
		buttons[i]->free();
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

int Menu::buttonPress(int x, int y) {
	for (unsigned int i = 0; i < buttons.size(); ++i) {
		if ((x > buttons[i]->getposB().x + SCREEN_X && x < (buttons[i]->getposB().x + buttons[i]->getWidth() + SCREEN_X))
			&& (y > buttons[i]->getposB().y + SCREEN_Y && y < (buttons[i]->getposB().y + buttons[i]->getHeight() + SCREEN_Y))) {
			return i + 1;
		}
	}
	return -1;
}