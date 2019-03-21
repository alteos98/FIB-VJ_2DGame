#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"

#define VELOCITY 10

enum PlayerAnims
{
	STAND_LEFT_DOWN, STAND_RIGHT_DOWN, MOVE_LEFT_DOWN, MOVE_RIGHT_DOWN,
	STAND_LEFT_UP, STAND_RIGHT_UP, MOVE_LEFT_UP, MOVE_RIGHT_UP,
	DEAD
};

void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, bool isOnFloor)
{
	playerSize = glm::ivec2(64, 64);
	bJumping = bGravity = false;
	this->isOnFloor = isOnFloor;
	fallStep = 14;

	spritesheet.loadFromFile("images/Player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(playerSize, glm::vec2(1.f/6.f, 1.f/6.f), &spritesheet, &shaderProgram);
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

	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::update(int deltaTime) {
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
		if (isOnFloor) {
			if (sprite->animation() != MOVE_LEFT_DOWN)
				sprite->changeAnimation(MOVE_LEFT_DOWN);
			posPlayer.x -= VELOCITY;
			if (map->collisionMoveLeft(posPlayer, playerSize))
			{
				posPlayer.x += VELOCITY;
				sprite->changeAnimation(STAND_LEFT_DOWN);
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
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
		if (isOnFloor) {
			if (sprite->animation() != MOVE_RIGHT_DOWN)
				sprite->changeAnimation(MOVE_RIGHT_DOWN);
			posPlayer.x += VELOCITY;
			if (map->collisionMoveRight(posPlayer, playerSize))
			{
				posPlayer.x -= VELOCITY;
				sprite->changeAnimation(STAND_RIGHT_DOWN);
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
			if (map->collisionMoveDown(posPlayer, playerSize, &posPlayer.y, fallStep)) {
				bGravity = false;
				isOnFloor = true;
			}
		}
		else {
			posPlayer.y -= fallStep;
			if (map->collisionMoveUp(posPlayer, playerSize, &posPlayer.y, fallStep)) {
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
			if (map->collisionMoveUp(posPlayer, playerSize, &posPlayer.y, fallStep)) {
				if (Game::instance().getKey(' ') && Game::instance().getCanInvertGravity()) {
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
			if (map->collisionMoveDown(posPlayer, playerSize, &posPlayer.y, fallStep)) {
				if (Game::instance().getKey(' ') && Game::instance().getCanInvertGravity()) {
					bGravity = true;
					Game::instance().setCanInvertGravity(false);
				}
			}
		}
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
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

glm::ivec2 Player::getPosition() {
	return posPlayer;
}

bool Player::getIsOnFloor() {
	return isOnFloor;
}

Sprite* Player::getSprite() {
	return sprite;
}

void Player::setAnimation(int i) {
	sprite->changeAnimation(i);
}

void Player::setIsOnFloor(bool floor)
{
	isOnFloor = floor;
}

int Player::getWidth()
{
	return playerSize.x;
}

int Player::getHeight()
{
	return playerSize.y;
}

int Player::getFallStep() {
	return fallStep;
}

bool Player::getBGravity() {
	return bGravity;
}