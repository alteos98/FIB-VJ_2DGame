#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Plataforma.h"
#include "Game.h"

enum PlataformaAnims
{
	BASE
};

void Plataforma::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::vec2 relation, string nameImage, glm::ivec2 posInicial, glm::ivec2 posFinal, int velocity)
{
	platSize = glm::ivec2(96, 32);
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
	sprite = Sprite::createSprite(platSize, relation, &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(BASE, 1);
	sprite->addKeyframe(BASE, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlat.x), float(tileMapDispl.y + posPlat.y)));

}

void Plataforma::newPosition() {
	if (goingReturning) {
		if (nMovement == nTotalMovements) {
			posPlat.x = posFinal.x;
			posPlat.y = posFinal.y;
			nMovement = nTotalMovements - 1;
			goingReturning = !goingReturning;
		}
		else { // nMovement < nTotalMovements
			posPlat.x = posInicial.x + nMovement * (int)incrementX * velocity;
			posPlat.y = posInicial.y + nMovement * (int)incrementY * velocity;
			nMovement++;
		}
	}
	else {
		if (nMovement == 0) {
			posPlat.x = posInicial.x;
			posPlat.y = posInicial.y;
			nMovement = 1;
			goingReturning = !goingReturning;
		}
		else { // nMovement > 0
			posPlat.x = posInicial.x + nMovement * (int)incrementX * velocity;
			posPlat.y = posInicial.y + nMovement * (int)incrementY * velocity;
			nMovement--;
		}
	}
}

void Plataforma::update(int deltaTime) {
	sprite->update(deltaTime);
	newPosition();
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlat.x), float(tileMapDispl.y + posPlat.y)));
}

void Plataforma::render()
{
	sprite->render();
}

void Plataforma::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Plataforma::setPosition(const glm::vec2 &pos)
{
	posPlat = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlat.x), float(tileMapDispl.y + posPlat.y)));
}

glm::ivec2 Plataforma::getPosition() {
	return posPlat;
}

void Plataforma::setAnimation(int i) {
	sprite->changeAnimation(i);
}

int Plataforma::getWidth()
{
	return platSize.x;
}

int Plataforma::getHeight()
{
	return platSize.y;
}

glm::ivec2 Plataforma::getIncrease() {
	int val;
	if (goingReturning) {
		val = 1;
	}
	else val = -1;
	return glm::ivec2(val * (int)incrementX * velocity, val * (int)incrementY * velocity);
}