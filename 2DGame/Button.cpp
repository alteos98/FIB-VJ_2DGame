#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Button.h"
#include "Game.h"

#define WIDTH 32
#define HEIGHT 16


enum ButtonAnims
{
	BASE
};

void Button::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram, glm::ivec2 buttonSize, glm::vec2 relation, string nameImage)
{
	this->buttonSize = buttonSize;

	spritesheet.loadFromFile(nameImage, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(buttonSize.x, buttonSize.y), relation, &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	
	sprite->setAnimationSpeed(BASE, 1);
	sprite->addKeyframe(BASE, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posButton.x), float(tileMapDispl.y + posButton.y)));

}

void Button::update(int deltaTime) {
	sprite->changeAnimation(BASE);
}

void Button::render() {
	sprite->render();
}

void Button::free() {
	sprite->free();
}

void Button::setTileMap(TileMap *tileMap) {
	map = tileMap;
}

void Button::setPosition(const glm::vec2 &pos) {
	posButton = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posButton.x), float(tileMapDispl.y + posButton.y)));
}

glm::vec2 Button::getposB()
{
	return posButton;
}

int Button::getWidth()
{
	return buttonSize.x;
}

int Button::getHeight()
{
	return buttonSize.y;
}


