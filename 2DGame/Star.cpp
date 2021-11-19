#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Star.h"
#include "Game.h"

enum StarAnims
{
	ROTATING
};

Star::Star()
{
}

Star::~Star()
{
}

void Star::init(const glm::ivec2 & posStar, ShaderProgram & shaderProgram, glm::ivec2 starSize)
{
	this->starSize = starSize;
	this->posStar = posStar;
	spritesheet.loadFromFile("images/star/star.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(starSize.x, starSize.y), glm::vec2(1.f / 5.f, 1.f / 3.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(ROTATING, 10);
	sprite->addKeyframe(ROTATING, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(ROTATING, glm::vec2(1.f / 5.f, 0.f));
	sprite->addKeyframe(ROTATING, glm::vec2(2.f / 5.f, 0.f));
	sprite->addKeyframe(ROTATING, glm::vec2(3.f / 5.f, 0.f));
	sprite->addKeyframe(ROTATING, glm::vec2(4.f / 5.f, 0.f));
	sprite->addKeyframe(ROTATING, glm::vec2(0.f, 1.f / 3.f));
	sprite->addKeyframe(ROTATING, glm::vec2(1.f / 5.f, 1.f / 3.f));
	sprite->addKeyframe(ROTATING, glm::vec2(2.f / 5.f, 1.f / 3.f));
	sprite->addKeyframe(ROTATING, glm::vec2(3.f / 5.f, 1.f / 3.f));
	sprite->addKeyframe(ROTATING, glm::vec2(4.f / 5.f, 1.f / 3.f));
	sprite->addKeyframe(ROTATING, glm::vec2(0.f, 2.f / 3.f));
	sprite->addKeyframe(ROTATING, glm::vec2(1.f / 5.f, 2.f / 3.f));

	sprite->changeAnimation(ROTATING);
	sprite->setPosition(glm::vec2(float(posStar.x), float(posStar.y)));
}

void Star::update(int deltaTime) {
	sprite->update(deltaTime);
}

void Star::render() {
	sprite->render();
}

void Star::setTileMap(TileMap *tileMap) {
	map = tileMap;
}

void Star::setPosition(const glm::vec2 &pos) {
	posStar = pos;
	sprite->setPosition(glm::vec2(float(posStar.x), float(posStar.y)));
}

glm::ivec2 Star::getPosition()
{
	return posStar;
}

int Star::getWidth()
{
	return starSize.x;
}

int Star::getHeight()
{
	return starSize.y;
}
