#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"

#define VELOCITY 2

enum EnemyAnims
{
	BASE
};

void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::vec2 relation, string nameImage, glm::ivec2 posInicial, glm::ivec2 posFinal)
{
	quadSize = glm::ivec2(64, 64);
	this->posInicial = posInicial;
	this->posFinal = posFinal;

	int x = posFinal.x - posInicial.x;
	int y = posFinal.y - posInicial.y;
	if (x > y)
		nTotalMovements = x / VELOCITY;
	else
		nTotalMovements = y / VELOCITY;
	incrementX = (float)x / nTotalMovements;
	incrementY = (float)y / nTotalMovements;
	nMovement = 0;
	goingReturning = true;

	spritesheet.loadFromFile(nameImage, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(quadSize, relation, &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(BASE, 8);
	sprite->addKeyframe(BASE, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Enemy::newPosition() {
	if (goingReturning) {
		if (nMovement >= nTotalMovements) {
			posEnemy.x = posFinal.x;
			posEnemy.y = posFinal.y;
			nMovement = nTotalMovements - 1;
			goingReturning = !goingReturning;
		}
		else { // nMovement < nTotalMovements
			posEnemy.x += int(incrementX * VELOCITY);
			posEnemy.y += int(incrementY * VELOCITY);
			nMovement++;
		}
	}
	else {
		if (nMovement <= 0) {
			posEnemy.x = posInicial.x;
			posEnemy.y = posInicial.y;
			nMovement = 1;
			goingReturning = !goingReturning;
		}
		else { // nMovement > 0
			posEnemy.x += int(incrementX * VELOCITY);
			posEnemy.y += int(incrementY * VELOCITY);
			nMovement--;
		}
	}
}

void Enemy::update(int deltaTime) {
	sprite->update(deltaTime);
	newPosition();
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy::render()
{
	sprite->render();
}

void Enemy::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2 &pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

glm::ivec2 Enemy::getPosition() {
	return posEnemy;
}

void Enemy::setAnimation(int i) {
	sprite->changeAnimation(i);
}