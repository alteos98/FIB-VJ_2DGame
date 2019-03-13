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
	if (isPlaying)
		level.update(deltaTime);
	else
		menu.update(deltaTime);
	
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
}

void Game::mousePress(int button, int x, int y)
{
	switch (actualMenu) {
	case MAINMENU:
	{
		switch (menu.ButtonPress(x, y)) {
		case 1: {
			updateMenu(SELECTDIFFICULTY);
			break;
		}
		case 2: {
			updateMenu(INSTRUCTIONS);
			break;
		}
		case 3: {
			updateMenu(CREDITS);
			break;
		}
		}
		break;
	}
	}
}

void Game::mouseRelease(int button)
{
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
		string sprites[3]{
			"images/buttonPlay.png",
			"images/GO.png",
			"images/buttonCredits.png"
		};
		glm::vec2 positions[3]{
			glm::vec2(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 45),
			glm::vec2(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 10),
			glm::vec2(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 25)
		};
		glm::ivec2 sizeButtons[3]{
			glm::ivec2(100, 30),
			glm::ivec2(100, 30),
			glm::ivec2(100, 30)
		};
		glm::vec2 relation[3]{
			glm::vec2(1.f, 1.f/4.f),
			glm::vec2(1.f, 1.f),
			glm::vec2(1.f, 1.f / 4.f)
		};
		menu.loadMenu(sprites, positions, sizeButtons, relation, 3);
		break;
	}
	case SELECTDIFFICULTY:
	{
		string sprites[2]{
			"images/buttonHelp.png",
			"images/buttonPlay.png"
		};
		glm::vec2 positions[2]{
			glm::vec2(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 45),
			glm::vec2(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 10)
		};
		glm::ivec2 sizeButtons[2]{
			glm::ivec2(100, 30),
			glm::ivec2(100, 30)
		};
		glm::vec2 relation[2]{
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f)
		};
		menu.loadMenu(sprites, positions, sizeButtons, relation, 2);
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