#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 6


enum PlayerAnims
{
	STAND_LEFT_DOWN, STAND_RIGHT_DOWN, MOVE_LEFT_DOWN, MOVE_RIGHT_DOWN,
	STAND_LEFT_UP, STAND_RIGHT_UP, MOVE_LEFT_UP, MOVE_RIGHT_UP
};

void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, bool isOnFloor)
{
	bJumping = bGravity = false;
	this->isOnFloor = isOnFloor;

	spritesheet.loadFromFile("images/Player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f/6.f, 1.f/6.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);

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

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::update(int deltaTime) {
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
		if (isOnFloor) {
			if (sprite->animation() != MOVE_LEFT_DOWN)
				sprite->changeAnimation(MOVE_LEFT_DOWN);
			posPlayer.x -= 5;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x += 5;
				sprite->changeAnimation(STAND_LEFT_DOWN);
			}
		}
		else {
			if (sprite->animation() != MOVE_LEFT_UP)
				sprite->changeAnimation(MOVE_LEFT_UP);
			posPlayer.x -= 5;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x += 5;
				sprite->changeAnimation(STAND_LEFT_UP);
			}
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
		if (isOnFloor) {
			if (sprite->animation() != MOVE_RIGHT_DOWN)
				sprite->changeAnimation(MOVE_RIGHT_DOWN);
			posPlayer.x += 5;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x -= 5;
				sprite->changeAnimation(STAND_RIGHT_DOWN);
			}
		}
		else {
			if (sprite->animation() != MOVE_RIGHT_UP)
				sprite->changeAnimation(MOVE_RIGHT_UP);
			posPlayer.x += 5;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x -= 5;
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
			posPlayer.y += FALL_STEP;
			if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y, FALL_STEP)) {
				bGravity = false;
				isOnFloor = true;
			}
		}
		else {
			posPlayer.y -= FALL_STEP;
			if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32), &posPlayer.y, FALL_STEP)) {
				bGravity = false;
				isOnFloor = false;
			}
		}
	}
	else {
		if (!isOnFloor) {
			posPlayer.y -= FALL_STEP;
			if (sprite->animation() == STAND_LEFT_DOWN)
				sprite->changeAnimation(STAND_LEFT_UP);
			else if (sprite->animation() == STAND_RIGHT_DOWN)
				sprite->changeAnimation(STAND_RIGHT_UP);
			if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32), &posPlayer.y, FALL_STEP)) {
				if (Game::instance().getKey(' ')) {
					bGravity = true;
				}
			}
		}
		else {
			posPlayer.y += FALL_STEP;
			if (sprite->animation() == STAND_LEFT_UP)
				sprite->changeAnimation(STAND_LEFT_DOWN);
			else if (sprite->animation() == STAND_RIGHT_UP)
				sprite->changeAnimation(STAND_RIGHT_DOWN);
			if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y, FALL_STEP)) {
				if (Game::instance().getKey(' ')) {
					bGravity = true;
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