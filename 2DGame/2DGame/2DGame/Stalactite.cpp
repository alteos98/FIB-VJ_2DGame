#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Stalactite.h"
#include "Game.h"

enum StalactiteAnims
{
	BASE
};

Stalactite::Stalactite()
{
	leftX = rightX = downY = NULL;
}

Stalactite::~Stalactite()
{
}

void Stalactite::init(const glm::ivec2 & stalactitePos, ShaderProgram & shaderProgram, glm::ivec2 stalactiteSize)
{
	this->stalactiteSize = stalactiteSize;
	this->stalactitePos = stalactitePos;
	this->fallingVelocity = 10;
	this->falling = false;

	spritesheet.loadFromFile("images/spikes/spikes.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(stalactiteSize, glm::vec2(1.f, 1.f / 2.f), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(BASE, 1);
	sprite->addKeyframe(BASE, glm::vec2(0.f, 1.f / 2.f));

	sprite->changeAnimation(BASE);
	sprite->setPosition(glm::vec2(float(stalactitePos.x), float(stalactitePos.y)));
}

void Stalactite::update(int deltaTime) {
	if (falling) {
		stalactitePos.y += 1 * fallingVelocity;
	}
	sprite->setPosition(glm::vec2(float(stalactitePos.x), float(stalactitePos.y)));
	sprite->update(deltaTime);
}

void Stalactite::render() {
	sprite->render();
}

void Stalactite::changeAnimation(int i) {
	sprite->changeAnimation(i);
}


// MY FUNCTIONS

bool Stalactite::hasToFall(glm::ivec2 & playerPos) {
	return (playerPos.x > leftX
		&& playerPos.x < rightX
		&& playerPos.y < downY
		&& playerPos.y > stalactitePos.y);
}

bool Stalactite::outOfMap() {
	if (stalactitePos.y > SCREEN_HEIGHT)
		return true;
	else
		return false;
}


// SETTERS

void Stalactite::setTileMap(TileMap *tileMap) {
	map = tileMap;
}

void Stalactite::setPosition(const glm::vec2 &pos) {
	stalactitePos = pos;
	sprite->setPosition(glm::vec2(float(stalactitePos.x), float(stalactitePos.y)));
}

void Stalactite::setMargin(int marginX, int marginY) {
	leftX = stalactitePos.x - marginX;
	rightX = stalactitePos.x + stalactiteSize.x + marginX;
	downY = stalactitePos.y + stalactiteSize.y + marginY;
}

void Stalactite::setLeftX(int leftX) {
	this->leftX = leftX;
}

void Stalactite::setRightX(int rightX) {
	this->rightX = rightX;
}

void Stalactite::setDownY(int downY) {
	this->downY = downY;
}

void Stalactite::setFallingVelocity(int fallingVelocity) {
	this->fallingVelocity = fallingVelocity;
}

void Stalactite::setFalling(bool b) {
	this->falling = b;
}


// GETTERS

glm::ivec2 Stalactite::getPosition()
{
	return stalactitePos;
}

int Stalactite::getWidth()
{
	return stalactiteSize.x;
}

int Stalactite::getHeight()
{
	return stalactiteSize.y;
}

int Stalactite::getLeftX() {
	return leftX;
}

int Stalactite::getRightX() {
	return rightX;
}

int Stalactite::getDownY() {
	return downY;
}

int Stalactite::getFallingVelocity() {
	return fallingVelocity;
}

bool Stalactite::getFalling() {
	return falling;
}