#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Spike.h"
#include "Game.h"

#define WIDTH 32
#define HEIGHT 16


enum SpikeAnims
{
	UP, DOWN
};

Spike::Spike()
{
}

Spike::~Spike()
{
}

void Spike::init(const glm::ivec2 & posSpike, ShaderProgram & shaderProgram, glm::ivec2 spikeSize, bool upOrDown)
{
	this->spikeSize = spikeSize;
	this->posSpike = posSpike;
	spritesheet.loadFromFile("images/spikes/spikes.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(spikeSize.x, spikeSize.y), glm::vec2(1.f, 1.f/2.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(UP, 1);
	sprite->addKeyframe(UP, glm::vec2(0.f, 1.f / 2.f));

	sprite->setAnimationSpeed(DOWN, 1);
	sprite->addKeyframe(DOWN, glm::vec2(0.f, 0.f));

	if (upOrDown)
		sprite->changeAnimation(UP);
	else
		sprite->changeAnimation(DOWN);
	sprite->setPosition(glm::vec2(float(posSpike.x), float(posSpike.y)));
}

void Spike::update(int deltaTime) {
	sprite->update(deltaTime);
}

void Spike::render() {
	sprite->render();
}

void Spike::setTileMap(TileMap *tileMap) {
	map = tileMap;
}

void Spike::setPosition(const glm::vec2 &pos) {
	posSpike = pos;
	sprite->setPosition(glm::vec2(float(posSpike.x), float(posSpike.y)));
}

glm::ivec2 Spike::getPosition()
{
	return posSpike;
}

int Spike::getWidth()
{
	return spikeSize.x;
}

int Spike::getHeight()
{
	return spikeSize.y;
}
