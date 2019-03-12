#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Button.h"
#include "Game.h"

#define WIDTH 32
#define HEIGHT 16


enum ButtonAnims
{
	GO
};

void Button::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	spritesheet.loadFromFile("images/GO.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(WIDTH, HEIGHT), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	
	sprite->setAnimationSpeed(GO, 1);
	sprite->addKeyframe(GO, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posButton.x), float(tileMapDispl.y + posButton.y)));

}

void Button::update(int deltaTime) {
	sprite->changeAnimation(GO);
}

void Button::render() {
	{
		sprite->render();
	}
}

void Button::setTileMap(TileMap *tileMap) {
	map = tileMap;
}

void Button::setPosition(const glm::vec2 &pos) {
	posButton = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posButton.x), float(tileMapDispl.y + posButton.y)));
}

glm::vec2 Button::getposB()
{
	return posButton;
}

int Button::getWidth()
{
	return WIDTH;
}

int Button::getHeight()
{
	return HEIGHT;
}


