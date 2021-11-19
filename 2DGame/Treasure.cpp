#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Treasure.h"
#include "Game.h"

enum TreasureAnims
{
	CLOSED, OPENED
};

Treasure::Treasure()
{
}

Treasure::~Treasure()
{
}

void Treasure::init(const glm::ivec2 & treasurePos, ShaderProgram & shaderProgram, glm::ivec2 treasureSize)
{
	this->treasureSize = treasureSize;
	this->treasurePos = treasurePos;

	spritesheet.loadFromFile("images/Treasure/treasure.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(treasureSize, glm::vec2(1.f / 2.f, 1.f), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(2);
	sprite->setAnimationSpeed(CLOSED, 1);
	sprite->addKeyframe(CLOSED, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(OPENED, 1);
	sprite->addKeyframe(OPENED, glm::vec2(1.f / 2.f, 0.f));

	sprite->changeAnimation(CLOSED);
	sprite->setPosition(glm::vec2(float(treasurePos.x), float(treasurePos.y)));
}

void Treasure::update(int deltaTime) {
	sprite->setPosition(glm::vec2(float(treasurePos.x), float(treasurePos.y)));
	sprite->update(deltaTime);
}

void Treasure::render() {
	sprite->render();
}

void Treasure::changeAnimation(int i) {
	sprite->changeAnimation(i);
}


// MY FUNCTIONS

void Treasure::open() {
	sprite->changeAnimation(OPENED);
}


// SETTERS

void Treasure::setTileMap(TileMap *tileMap) {
	map = tileMap;
}

void Treasure::setPosition(const glm::vec2 &pos) {
	treasurePos = pos;
	sprite->setPosition(glm::vec2(float(treasurePos.x), float(treasurePos.y)));
}


// GETTERS

glm::ivec2 Treasure::getPosition()
{
	return treasurePos;
}

int Treasure::getWidth()
{
	return treasureSize.x;
}

int Treasure::getHeight()
{
	return treasureSize.y;
}