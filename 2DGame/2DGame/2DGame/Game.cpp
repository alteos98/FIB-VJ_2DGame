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
	case MAINMENU: {
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
	case SELECTDIFFICULTY: {
		switch (menu.ButtonPress(x, y)) {
		case 1: {
			updateMenu(PLAYING);
			isPlaying = true;
			int difficulty = 1;
			level.init(difficulty);
			break;
		}
		case 2: {
			updateMenu(PLAYING);
			isPlaying = true;
			difficulty = 2;
			level.init(difficulty);
			break;
		}
		case 3: {
			updateMenu(MAINMENU);
			break;
		}
		}
		break;
	}
	case INSTRUCTIONS: {
		if (menu.ButtonPress(x, y) == 1) {
			updateMenu(MAINMENU);
		}
	}
	case CREDITS: {
		if (menu.ButtonPress(x, y) == 1) {
			updateMenu(MAINMENU);
		}
	}
	case PAUSE: {
		/*switch (menu.ButtonPress(x, y)) {
		}*/
	}
	case ENDSCREEN: {
		switch (menu.ButtonPress(x, y)) {
		case 1: {
			updateMenu(PLAYING);
			isPlaying = true;
			level.init(difficulty);
			break;
		}
		case 2: {
			updateMenu(SELECTDIFFICULTY);
			isPlaying = false;
			break;
		}
		}
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
		const int nButtons = 3;
		string sprites[nButtons]{
			"images/buttons/PlayButton.png",
			"images/buttons/InstructionsButton.png",
			"images/buttons/CreditsButton.png"
		};
		glm::vec2 positions[nButtons]{
			glm::vec2(SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT / 2 - 80),
			glm::vec2(SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT / 2 - 0),
			glm::vec2(SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT / 2 + 80)
		};
		glm::ivec2 sizeButtons[nButtons]{
			glm::ivec2(256, 64),
			glm::ivec2(256, 64),
			glm::ivec2(256, 64)
		};
		glm::vec2 relation[nButtons]{
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f)
		};
		menu.loadMenu(sprites, positions, sizeButtons, relation, nButtons);
		break;
	}
	case SELECTDIFFICULTY:
	{
		const int nButtons = 3;
		string sprites[nButtons]{
			"images/buttons/EasyModeButton.png",
			"images/buttons/HardModeButton.png",
			"images/buttons/BackButton.png"
		};
		glm::vec2 positions[nButtons]{
			glm::vec2(SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT / 2 - 70),
			glm::vec2(SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT / 2 + 10),
			glm::vec2(15, SCREEN_HEIGHT - 47)
		};
		glm::ivec2 sizeButtons[nButtons]{
			glm::ivec2(256, 64),
			glm::ivec2(256, 64),
			glm::ivec2(64, 32)
		};
		glm::vec2 relation[nButtons]{
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f)
		};
		menu.loadMenu(sprites, positions, sizeButtons, relation, nButtons);
		break;
	}
	case PLAYING:
	{
		break;
	}
	case INSTRUCTIONS:
	{
		const int nButtons = 1;
		string sprites[nButtons]{
			"images/buttons/BackButton.png"
		};
		glm::vec2 positions[nButtons]{
			glm::vec2(15, SCREEN_HEIGHT - 47)
		};
		glm::ivec2 sizeButtons[nButtons]{
			glm::ivec2(64, 32)
		};
		glm::vec2 relation[nButtons]{
			glm::vec2(1.f, 1.f / 4.f)
		};
		menu.loadMenu(sprites, positions, sizeButtons, relation, nButtons);
		break;
	}
	case CREDITS:
	{
		const int nButtons = 1;
		string sprites[nButtons]{
			"images/buttons/BackButton.png"
		};
		glm::vec2 positions[nButtons]{
			glm::vec2(15, SCREEN_HEIGHT - 47)
		};
		glm::ivec2 sizeButtons[nButtons]{
			glm::ivec2(64, 32)
		};
		glm::vec2 relation[nButtons]{
			glm::vec2(1.f, 1.f / 4.f)
		};
		menu.loadMenu(sprites, positions, sizeButtons, relation, nButtons);
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