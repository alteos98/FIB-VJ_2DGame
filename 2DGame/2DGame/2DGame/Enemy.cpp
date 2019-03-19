#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"

enum EnemyAnims
{
	BASE
};

void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::vec2 relation, string nameImage, glm::ivec2 posInicial, glm::ivec2 posFinal, int velocity)
{
	enemySize = glm::ivec2(64, 64);
	this->posInicial = posInicial;
	this->posFinal = posFinal;
	this->velocity = velocity;

	int x = posFinal.x - posInicial.x;
	int y = posFinal.y - posInicial.y;
	if (abs(x) > abs(y))
		nTotalMovements = abs(x) / velocity;
	else
		nTotalMovements = abs(y) / velocity;
	incrementX = (float)x / ((float)nTotalMovements * (float)velocity);
	incrementY = (float)y / ((float)nTotalMovements * (float)velocity);
	nMovement = 1;
	goingReturning = true;

	spritesheet.loadFromFile(nameImage, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(enemySize, relation, &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(BASE, 1);
	sprite->addKeyframe(BASE, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Enemy::newPosition() {
	if (goingReturning) {
		if (nMovement == nTotalMovements) {
			posEnemy.x = posFinal.x;
			posEnemy.y = posFinal.y;
			nMovement = nTotalMovements - 1;
			goingReturning = !goingReturning;
		}
		else { // nMovement < nTotalMovements
			posEnemy.x = posInicial.x + nMovement * (int)incrementX * velocity;
			posEnemy.y = posInicial.y + nMovement * (int)incrementY * velocity;
			nMovement++;
		}
	}
	else {
		if (nMovement == 0) {
			posEnemy.x = posInicial.x;
			posEnemy.y = posInicial.y;
			nMovement = 1;
			goingReturning = !goingReturning;
		}
		else { // nMovement > 0
			posEnemy.x = posInicial.x + nMovement * (int)incrementX * velocity;
			posEnemy.y = posInicial.y + nMovement * (int)incrementY * velocity;
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

int Enemy::getWidth()
{
	return enemySize.x;
}

int Enemy::getHeight()
{
	return enemySize.y;
}