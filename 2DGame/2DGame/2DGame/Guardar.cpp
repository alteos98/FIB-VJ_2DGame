#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Guardar.h"
#include "Game.h"

#define WIDTH 32
#define HEIGHT 16


enum GuardarAnims
{
	BASE, LLAMA_ROJA, LLAMA_AZUL
};

void Guardar::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram, glm::ivec2 guardarSize, int id)
{
	this->GuardarSize = guardarSize;
	this->id = id;
	spritesheet.loadFromFile("images/guardar/llamas.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteBase = Sprite::createSprite(glm::ivec2(guardarSize.x, guardarSize.y),glm::vec2(1.f / 4.f, 1.f / 4.f) , &spritesheet, &shaderProgram);
	sprite = Sprite::createSprite(glm::ivec2(guardarSize.x, guardarSize.y), glm::vec2(1.f / 4.f, 1.f / 4.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);
	spriteBase->setNumberAnimations(1);

	spriteBase->setAnimationSpeed(BASE, 1);
	spriteBase->addKeyframe(BASE, glm::vec2(0.f, 2.f / 4.f));

	sprite->setAnimationSpeed(LLAMA_AZUL, 8);
	sprite->addKeyframe(LLAMA_AZUL, glm::vec2(0.f, 1.f / 4.f));
	sprite->addKeyframe(LLAMA_AZUL, glm::vec2(1.f / 4.f, 1.f / 4.f));
	sprite->addKeyframe(LLAMA_AZUL, glm::vec2(2.f / 4.f, 1.f / 4.f));
	sprite->addKeyframe(LLAMA_AZUL, glm::vec2(3.f / 4.f, 1.f / 4.f));

	sprite->setAnimationSpeed(LLAMA_ROJA, 8);
	sprite->addKeyframe(LLAMA_ROJA, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(LLAMA_ROJA, glm::vec2(1.f / 4.f, 0.f));
	sprite->addKeyframe(LLAMA_ROJA, glm::vec2(2.f / 4.f, 0.f));
	sprite->addKeyframe(LLAMA_ROJA, glm::vec2(3.f / 4.f, 0.f));

	spriteBase->changeAnimation(0);
	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGuardar.x), float(tileMapDispl.y + posGuardar.y)));
	spriteBase->setPosition(glm::vec2(float(tileMapDispl.x + posGuardar.x), float(tileMapDispl.y + posGuardar.y + 64)));
}

void Guardar::update(int deltaTime) {
	sprite->update(deltaTime);
	//sprite->changeAnimation(LLAMA_AZUL);
	//sprite->changeAnimation(LLAMA_ROJA);
	spriteBase->update(deltaTime);
	//spriteBase->changeAnimation(BASE);
}

void Guardar::render() {
	sprite->render();
	spriteBase->render();
}

int Guardar::getID()
{
	return id;
}

void Guardar::setTileMap(TileMap *tileMap) {
	map = tileMap;
}

void Guardar::setPosition(const glm::vec2 &pos) {
	posGuardar = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGuardar.x), float(tileMapDispl.y + posGuardar.y)));
	spriteBase->setPosition(glm::vec2(float(tileMapDispl.x + posGuardar.x), float(tileMapDispl.y + posGuardar.y + 64)));
}

glm::ivec2 Guardar::getposG()
{
	return posGuardar;
}

int Guardar::getWidth()
{
	return GuardarSize.x;
}

int Guardar::getHeight()
{
	return GuardarSize.y;
}

void Guardar::Cambiar_llama(bool llama) {
	if (llama)
		sprite->changeAnimation(LLAMA_AZUL);
	else sprite->changeAnimation(LLAMA_ROJA);

}
