#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Lightning.h"
#include "Game.h"

enum LightningAnims
{
	BASE
};

Lightning::Lightning()
{
	orientation = NULL;
}

Lightning::~Lightning()
{
}

void Lightning::init(const glm::ivec2 & posLightning, ShaderProgram & shaderProgram, glm::ivec2 lightningSize, bool orientation)
{
	this->lightningSize = lightningSize;
	this->posLightning = posLightning;
	this->orientation = orientation;

	if (orientation) {
		spritesheet.loadFromFile("images/lightning/lightning1.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(lightningSize, glm::vec2(1.f / 8.f, 1.f), &spritesheet, &shaderProgram);
		
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(BASE, 16);
		sprite->addKeyframe(BASE, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(BASE, glm::vec2(1.f / 8.f, 0.f));
		sprite->addKeyframe(BASE, glm::vec2(2.f / 8.f, 0.f));
		sprite->addKeyframe(BASE, glm::vec2(3.f / 8.f, 0.f));
		sprite->addKeyframe(BASE, glm::vec2(4.f / 8.f, 0.f));
		sprite->addKeyframe(BASE, glm::vec2(5.f / 8.f, 0.f));
		sprite->addKeyframe(BASE, glm::vec2(6.f / 8.f, 0.f));
		sprite->addKeyframe(BASE, glm::vec2(7.f / 8.f, 0.f));
	}
	else {
		spritesheet.loadFromFile("images/lightning/lightning2.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(lightningSize, glm::vec2(1.f, 1.f / 8.f), &spritesheet, &shaderProgram);
		
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(BASE, 16);
		sprite->addKeyframe(BASE, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(BASE, glm::vec2(0.f, 1.f / 8.f));
		sprite->addKeyframe(BASE, glm::vec2(0.f, 2.f / 8.f));
		sprite->addKeyframe(BASE, glm::vec2(0.f, 3.f / 8.f));
		sprite->addKeyframe(BASE, glm::vec2(0.f, 4.f / 8.f));
		sprite->addKeyframe(BASE, glm::vec2(0.f, 5.f / 8.f));
		sprite->addKeyframe(BASE, glm::vec2(0.f, 6.f / 8.f));
		sprite->addKeyframe(BASE, glm::vec2(0.f, 7.f / 8.f));
	}

	sprite->changeAnimation(BASE);
	sprite->setPosition(glm::vec2(float(posLightning.x), float(posLightning.y)));
}

void Lightning::update(int deltaTime) {
	sprite->update(deltaTime);
}

void Lightning::render() {
	sprite->render();
}

void Lightning::changeAnimation(int i) {
	sprite->changeAnimation(i);
}

void Lightning::setTileMap(TileMap *tileMap) {
	map = tileMap;
}

void Lightning::setPosition(const glm::vec2 &pos) {
	posLightning = pos;
	sprite->setPosition(glm::vec2(float(posLightning.x), float(posLightning.y)));
}

glm::ivec2 Lightning::getPosition()
{
	return posLightning;
}

int Lightning::getWidth()
{
	return lightningSize.x;
}

int Lightning::getHeight()
{
	return lightningSize.y;
}

bool Lightning::getOrientation() {
	return orientation;
}

void Lightning::setOrientation(bool orientation) {
	this->orientation = orientation;
}