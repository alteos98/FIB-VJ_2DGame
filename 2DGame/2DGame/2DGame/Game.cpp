#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <iostream>


void Game::init()
{
	bPlay = true;
	isPlaying = bLeft = false;
	actualMenu = MAINMENU;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	menu = Menu();
	level = Level();

	updateMenu(MAINMENU);
}

bool Game::update(int deltaTime)
{
	switch (actualMenu) {
	case MAINMENU:
	{
		if (keys['1']) {
			updateMenu(SELECTDIFFICULTY);
		}
		else if (keys['2']) {
			updateMenu(INSTRUCTIONS);
		}
		else if (keys['3']) {
			updateMenu(CREDITS);
		}
		break;
	}
	case SELECTDIFFICULTY:
	{
		if (keys['1']) {
			updateMenu(PLAYING);
			isPlaying = true;
			easyDifficulty = true;
			level.init(easyDifficulty);
		}
		else if (keys['2']) {
			updateMenu(PLAYING);
			isPlaying = true;
			easyDifficulty = false;
			level.init(easyDifficulty);
		}
		else if (keys[27]) {
			updateMenu(MAINMENU);
		}
		break;
	}
	case PLAYING:
	{
		if (keys[27]) {
			updateMenu(PAUSE);
			isPlaying = false;
		}
		else {
			level.update(deltaTime);
		}
		break;
	}
	case INSTRUCTIONS:
	{
		if (keys[27]) {
			updateMenu(MAINMENU);
		}
		break;
	}
	case CREDITS:
	{
		if (keys[27]) {
			updateMenu(MAINMENU);
		}
		break;
	}
	case PAUSE:
	{
		if (keys[27]) {
			updateMenu(MAINMENU);
		}
		else if (keys[' ']) {
			updateMenu(PLAYING);
			isPlaying = true;
		}
		break;
	}
	case ENDSCREEN:
	{
		if (keys[27]) {
			updateMenu(MAINMENU);
		}
		else {
			for (int i = 0; i < 256 && !isPlaying; ++i) {
				if (keys[i] && !keys[27])
					updateMenu(PLAYING);
					isPlaying = true;
					level.init(easyDifficulty);
			}
		}
		break;
	}
	}
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (isPlaying)
		level.render();
	else
		menu.render();
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		if (actualMenu == MAINMENU)
			bPlay = false;

	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
	mouseX = x;
	mouseY = y;

	if (isPlaying) {}
	else
		menu.mouseMove(x, y, bLeft);
}

void Game::mousePress(int button)
{
	if (button == GLUT_LEFT_BUTTON)
		bLeft = true;

	if (isPlaying)
		level.render();
	else
		menu.mouseMove(mouseX, mouseY, bLeft);
}

void Game::mouseRelease(int button)
{
	if (button == GLUT_LEFT_BUTTON)
		bLeft = false;

	if (isPlaying)
		level.render();
	else
		menu.mouseReleased(mouseX, mouseY);
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

void Game::updateMenu(MenuTypes menuType) {
	actualMenu = menuType;

	switch (menuType) {
	case MAINMENU:
	{
		string sprites[4]{
			"images/buttonPlay.png",
			"images/buttonHelp.png",
			"images/buttonCredits.png"
		};
		glm::vec2 positions[4]{
			glm::vec2(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 45),
			glm::vec2(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 10),
			glm::vec2(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 25)
		};
		menu.init(sprites, positions, 3);
		break;
	}
	case SELECTDIFFICULTY:
	{
		string sprites[4]{
			"images/buttonHelp.png",
			"images/buttonPlay.png"
		};
		glm::vec2 positions[4]{
			glm::vec2(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 45),
			glm::vec2(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 10)
		};
		menu.init(sprites, positions, 2);
		break;
	}
	case PLAYING:
	{
		break;
	}
	case INSTRUCTIONS:
	{
		break;
	}
	case CREDITS:
	{
		break;
	}
	case PAUSE:
	{
		break;
	}
	case ENDSCREEN:
	{
		break;
	}
	}
}