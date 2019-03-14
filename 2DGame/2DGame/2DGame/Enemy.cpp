#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"

#define FALL_STEP 14
#define VELOCITY 10

enum EnemyAnims
{
	BASE
};

void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::vec2 relation, string nameImage)
{
	quadSize = glm::ivec2(64, 64);

	spritesheet.loadFromFile(nameImage, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(quadSize, relation, &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(BASE, 8);
	sprite->addKeyframe(BASE, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Enemy::update(int deltaTime) {
	sprite->update(deltaTime);
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