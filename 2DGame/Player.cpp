#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
//#include "AudioEngine.h"

#define VELOCITY 10
#define PI 3.141592

enum PlayerAnims
{
	STAND_LEFT_DOWN, STAND_RIGHT_DOWN, MOVE_LEFT_DOWN, MOVE_RIGHT_DOWN,
	STAND_LEFT_UP, STAND_RIGHT_UP, MOVE_LEFT_UP, MOVE_RIGHT_UP,
	DEAD
};

void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::ivec2 size, bool isOnFloor)
{
	hasdesplas = false;
	desplas = 0;
	time = 5 * float(PI) / 2;
	this->playerSize = size;
	this->isOnFloor = isOnFloor;
	this->shaderProgram = shaderProgram;
	bJumping = bGravity = false;
	fallStep = 16;

	spritesheet.loadFromFile("images/player/Player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	initSprite();
	sprite->changeAnimation(1);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::initSprite() {
	sprite = Sprite::createSprite(playerSize, glm::vec2(1.f / 6.f, 1.f / 6.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(9);

	sprite->setAnimationSpeed(STAND_LEFT_DOWN, 8);
	sprite->addKeyframe(STAND_LEFT_DOWN, glm::vec2(3.f / 6.f, 2.f / 6.f));

	sprite->setAnimationSpeed(STAND_RIGHT_DOWN, 8);
	sprite->addKeyframe(STAND_RIGHT_DOWN, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT_DOWN, 8);
	sprite->addKeyframe(MOVE_LEFT_DOWN, glm::vec2(3.f / 6.f, 2.f / 6.f));
	sprite->addKeyframe(MOVE_LEFT_DOWN, glm::vec2(2.f / 6.f, 2.f / 6.f));

	sprite->setAnimationSpeed(MOVE_RIGHT_DOWN, 8);
	sprite->addKeyframe(MOVE_RIGHT_DOWN, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT_DOWN, glm::vec2(1.f / 6.f, 0.f));

	sprite->setAnimationSpeed(STAND_LEFT_UP, 8);
	sprite->addKeyframe(STAND_LEFT_UP, glm::vec2(3.f / 6.f, 1.f / 6.f));

	sprite->setAnimationSpeed(STAND_RIGHT_UP, 8);
	sprite->addKeyframe(STAND_RIGHT_UP, glm::vec2(0.f, 3.f / 6.f));

	sprite->setAnimationSpeed(MOVE_LEFT_UP, 8);
	sprite->addKeyframe(MOVE_LEFT_UP, glm::vec2(3.f / 6.f, 1.f / 6.f));
	sprite->addKeyframe(MOVE_LEFT_UP, glm::vec2(2.f / 6.f, 1.f / 6.f));

	sprite->setAnimationSpeed(MOVE_RIGHT_UP, 8);
	sprite->addKeyframe(MOVE_RIGHT_UP, glm::vec2(0.f, 3.f / 6.f));
	sprite->addKeyframe(MOVE_RIGHT_UP, glm::vec2(1.f / 6.f, 3.f / 6.f));

	sprite->setAnimationSpeed(DEAD, 8);
	sprite->addKeyframe(DEAD, glm::vec2(5.f / 6.f, 0.f));
}

void Player::update(int deltaTime) {
	sprite->update(deltaTime);
	numtile = 0;
//	t = clock() - t;
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
		needdesplas = false;
		if(cambiosentido)sentidodesplas = -1;
	//  if (little) AudioEngine::instance().sonidos["pasos_g"].resume();
	//	else AudioEngine::instance().sonidos["pasos_g"].resume();
		if (isOnFloor) {
			if (sprite->animation() != MOVE_LEFT_DOWN)
				sprite->changeAnimation(MOVE_LEFT_DOWN);
			posPlayer.x -= VELOCITY;
			if (map->collisionMoveLeft(posPlayer, playerSize))
			{
				posPlayer.x += VELOCITY;
				sprite->changeAnimation(STAND_LEFT_DOWN);
			}
			else if (pasos % 10 == 0 && !bGravity) {
				/*
				if (!little) AudioEngine::instance().sonidos["pasos_g"].play(0);
				else AudioEngine::instance().sonidos["pasos_p"].play(0);
				*/
			}
		}
		else {
			if (sprite->animation() != MOVE_LEFT_UP)
				sprite->changeAnimation(MOVE_LEFT_UP);
			posPlayer.x -= VELOCITY;
			if (map->collisionMoveLeft(posPlayer, playerSize))
			{
				posPlayer.x += VELOCITY;
				sprite->changeAnimation(STAND_LEFT_UP);
			}
			else if (pasos % 10 == 0 && !bGravity) {
				/*
				if (!little) AudioEngine::instance().sonidos["pasos_g"].play(0);
				else AudioEngine::instance().sonidos["pasos_p"].play(0);
				*/
			}
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
		needdesplas = false;
		if (cambiosentido)sentidodesplas = +1;
		if (isOnFloor) {
			if (sprite->animation() != MOVE_RIGHT_DOWN)
				sprite->changeAnimation(MOVE_RIGHT_DOWN);
			posPlayer.x += VELOCITY;
			if (map->collisionMoveRight(posPlayer, playerSize))
			{
				posPlayer.x -= VELOCITY;
				sprite->changeAnimation(STAND_RIGHT_DOWN);
			}
			else if (pasos % 10 == 0 && !bGravity) {
				/*
				if (!little) AudioEngine::instance().sonidos["pasos_g"].play(0);
				else AudioEngine::instance().sonidos["pasos_p"].play(0);
				*/
			}
		}
		else {
			if (sprite->animation() != MOVE_RIGHT_UP)
				sprite->changeAnimation(MOVE_RIGHT_UP);
			posPlayer.x += VELOCITY;
			if (map->collisionMoveRight(posPlayer, playerSize))
			{
				posPlayer.x -= VELOCITY;
				sprite->changeAnimation(STAND_RIGHT_UP);
			}
			else if (pasos % 10 == 0 && !bGravity) {
				/*
				if (!little) AudioEngine::instance().sonidos["pasos_g"].play(0);
				else AudioEngine::instance().sonidos["pasos_p"].play(0);
				*/
			}
		}
	}
	else
	{
		if (isOnFloor) {
			if (sprite->animation() == MOVE_LEFT_DOWN)
				sprite->changeAnimation(STAND_LEFT_DOWN);
			else if (sprite->animation() == MOVE_RIGHT_DOWN)
				sprite->changeAnimation(STAND_RIGHT_DOWN);
		}
		else {
			if (sprite->animation() == MOVE_LEFT_UP)
				sprite->changeAnimation(STAND_LEFT_UP);
			else if (sprite->animation() == MOVE_RIGHT_UP)
				sprite->changeAnimation(STAND_RIGHT_UP);
		}
	}

	if (bGravity) {
		if (!isOnFloor) {
			posPlayer.y += fallStep;
			if (map->collisionMoveDown(posPlayer, playerSize, &posPlayer.y, fallStep, numtile)) {
				bGravity = false;
				isOnFloor = true;
			}
		}
		else {
			posPlayer.y -= fallStep;
			if (map->collisionMoveUp(posPlayer, playerSize, &posPlayer.y, fallStep, numtile)) {
				bGravity = false;
				isOnFloor = false;
			}
		}
	}
	else {
		if (!isOnFloor) {
			posPlayer.y -= fallStep;
			if (sprite->animation() == STAND_LEFT_DOWN)
				sprite->changeAnimation(STAND_LEFT_UP);
			else if (sprite->animation() == STAND_RIGHT_DOWN)
				sprite->changeAnimation(STAND_RIGHT_UP);
			if (map->collisionMoveUp(posPlayer, playerSize, &posPlayer.y, fallStep, numtile)) {
				if (Game::instance().getKey(' ') && Game::instance().getCanInvertGravity()) {
					/*
					if(little) AudioEngine::instance().sonidos["salto_p"].play(0);
					else AudioEngine::instance().sonidos["salto_g"].play(0);
					*/
					bGravity = true;
					Game::instance().setCanInvertGravity(false);
				}
			}
		}
		else {
			posPlayer.y += fallStep;
			if (sprite->animation() == STAND_LEFT_UP)
				sprite->changeAnimation(STAND_LEFT_DOWN);
			else if (sprite->animation() == STAND_RIGHT_UP)
				sprite->changeAnimation(STAND_RIGHT_DOWN);
			if (map->collisionMoveDown(posPlayer, playerSize, &posPlayer.y, fallStep, numtile)) {
				if (Game::instance().getKey(' ') && Game::instance().getCanInvertGravity()) {
					/*
					if (little) AudioEngine::instance().sonidos["salto_p"].play(0);
					else AudioEngine::instance().sonidos["salto_g"].play(0);
					*/
					bGravity = true;
					Game::instance().setCanInvertGravity(false);
				}
			}
		}
		
	}

	if (!Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !needdesplas && sentidodesplas == -1) {
		needdesplas = true;
		hasdesplas = true;
	}
	else if (!Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !needdesplas && sentidodesplas == 1 ) {
		needdesplas = true;
		hasdesplas = true;
	}
	pasos += 1; pasos %= 109;
	if (hasdesplas) posPlayer.x += int(-sentidodesplas) * aceleracion();
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

int Player::aceleracion() {
	if (numtile == 157 && hasdesplas) {
		ac = - pow(((time-48)/12),2) +2;
		time++;
		cambiosentido = false;
	}
	else {
		ac = 0;
		time = 0;
	}

	if (ac >= 0) {
		cambiosentido = true;
		ac = 0;
		time = 0;
		hasdesplas = false;
	}
	return (int)ac;
}


void Player::render()
{
	sprite->render();
}

// GETTERS

int Player::getWidth()
{
	return playerSize.x;
}

int Player::getHeight()
{
	return playerSize.y;
}

void Player::setGravity(bool b) {
	bGravity = b;
}

int Player::getFallStep() {
	return fallStep;
}

bool Player::getBGravity() {
	return bGravity;
}

bool Player::isLittle()
{
	return little;
}

glm::ivec2 Player::getPosition() {
	return posPlayer;
}

bool Player::getIsOnFloor() {
	return isOnFloor;
}

bool Player::getbGravity() {
	return bGravity;
}

Sprite* Player::getSprite() {
	return sprite;
}

TileMap* Player::getTileMap() {
	return map;
}

// SETTERS

void Player::setAnimation(int i) {
	sprite->changeAnimation(i);
}

void Player::setIsOnFloor(bool floor)
{
	isOnFloor = floor;
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::setSize(glm::ivec2 newSize) {
	this->playerSize = newSize;
}

void Player::setLittle(bool little)
{
	this->little = little;
}

void Player::setHasdesplas(bool b)
{
	hasdesplas = b;
}
 