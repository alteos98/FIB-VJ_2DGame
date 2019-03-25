#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <iostream>



void Game::init()
{
	bPlay = true;
	isPlaying = false;
	actualMenu = MAINMENU;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	AudioEngine::instance().init();
	AudioEngine::instance().dirmusica = "./Musics/";
	AudioEngine::instance().dirsonido = "./Sounds/";

	menu = Menu();
	menu.loadMusicAndSoundEffects();
	level = Level();
	level.LoadMusicAndSoundEffects();

	canInvertGravity = true;

	updateMenu(MAINMENU);
}

bool Game::update(int deltaTime)
{
	if (isPlaying && (level.getActualMap() == 15 || level.getActualMap() == 26) && level.collisionPlayerStar()) {
		isPlaying = false;
		updateMenu(ENDSCREEN);
	}

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
	if (key == 27) { // Escape code
		if (actualMenu == MAINMENU)
			bPlay = false;
	}

	if (isPlaying) {
		if (difficulty == 1) {
			if (key == '1') {
				level.setMap(11);
				level.setPlayerPosition(glm::vec2(300, 500));
				level.load();
			}
			else if (key == '2') {
				level.setMap(12);
				level.setPlayerPosition(glm::vec2(50, 500));
				level.load();
			}
			else if (key == '3') {
				level.setMap(13);
				level.setPlayerPosition(glm::vec2(50, 500));
				level.load();
			}
			else if (key == '4') {
				level.setMap(14);
				level.setPlayerPosition(glm::vec2(50, 100));
				level.load();
			}
			else if (key == '5') {
				level.setMap(15);
				level.setPlayerPosition(glm::vec2(50, 100));
				level.load();
			}
		}
		else if (difficulty == 2) {
			if (key == '1') {
				level.setMap(21);
				level.setPlayerPosition(glm::vec2(50, 600));
				level.load();
			}
			else if (key == '2') {
				level.setMap(22);
				level.setPlayerPosition(glm::vec2(50, 50));
				level.load();
			}
			else if (key == '3') {
				level.setMap(23);
				level.setPlayerPosition(glm::vec2(100, 50));
				level.load();
			}
			else if (key == '4') {
				level.setMap(24);
				level.setPlayerPosition(glm::vec2(50, 500));
				level.load();
			}
			else if (key == '5') {
				level.setMap(25);
				level.setPlayerPosition(glm::vec2(50, 600));
				level.load();
			}
			else if (key == '6') {
				level.setMap(26);
				level.setPlayerPosition(glm::vec2(200, 600));
				level.load();
			}
		}
	}

	keys[key] = true;
}

void Game::keyReleased(int key)
{
	if (key == ' ')
		canInvertGravity = true;
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
		switch (menu.buttonPress(x, y)) {
		case 1: {
			AudioEngine::instance().sonidos["okay"].play(0);
			menu.free();
			updateMenu(SELECTDIFFICULTY);
			break;
		}
		case 2: {
			AudioEngine::instance().sonidos["okay"].play(0);
			menu.free();
			updateMenu(INSTRUCTIONS);
			break;
		}
		case 3: {
			AudioEngine::instance().sonidos["okay"].play(0);
			menu.free();
			updateMenu(CREDITS);
			break;
		}
		}
		break;
	}
	case SELECTDIFFICULTY: {
		switch (menu.buttonPress(x, y)) {
		case 1: {
			AudioEngine::instance().sonidos["okay"].play(0);
			menu.free();
			updateMenu(PLAYING);
			isPlaying = true;
			difficulty = 1;
			level.init(difficulty);
			break;
		}
		case 2: {
			AudioEngine::instance().sonidos["okay"].play(0);
			menu.free();
			updateMenu(PLAYING);
			isPlaying = true;
			difficulty = 2;
			level.init(difficulty);
			break;
		}
		case 3: {
			AudioEngine::instance().sonidos["cancel"].play(0);
			menu.free();
			updateMenu(MAINMENU);
			break;
		}
		}
		break;
	}
	case INSTRUCTIONS: {
		if (menu.buttonPress(x, y) == 1) {
			AudioEngine::instance().sonidos["cancel"].play(0);
			menu.free();
			updateMenu(MAINMENU);
		}
		break;
	}
	case CREDITS: {
		if (menu.buttonPress(x, y) == 1) {
			AudioEngine::instance().sonidos["cancel"].play(0);
			menu.free();
			updateMenu(MAINMENU);
		}
		break;
	}
	case PAUSE: {
		switch (menu.buttonPress(x, y)) {
		case 1: {
			AudioEngine::instance().musicas["tite"].resume();
			AudioEngine::instance().sonidos["okay"].play(0);
			menu.free();
			updateMenu(PLAYING);
			isPlaying = true;
			break;
		}
		case 2: {
			AudioEngine::instance().sonidos["cancel"].play(0);
			menu.free();
			updateMenu(MAINMENU);
			isPlaying = false;
			break;
		}
		}
		break;
	}
	case ENDSCREEN: {
		switch (menu.buttonPress(x, y)) {
		case 1: {
			AudioEngine::instance().sonidos["okay"].play(0);
			menu.free();
			updateMenu(PLAYING);
			level.init(difficulty);
			isPlaying = true;
			break;
		}
		case 2: {
			AudioEngine::instance().sonidos["cancel"].play(0);
			menu.free();
			updateMenu(MAINMENU);
			isPlaying = false;
			break;
		}
		}
		break;
	}
	case PLAYING: {
		if (level.buttonPress(x, y)) {
			AudioEngine::instance().musicas["tite"].pause();
			AudioEngine::instance().sonidos["cancel"].play(0);
			isPlaying = false;
			updateMenu(PAUSE);
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
		const int nButtons = 3;
		string sprites[nButtons]{
			"images/buttons/PlayButton.png",
			"images/buttons/InstructionsButton.png",
			"images/buttons/CreditsButton.png"
		};
		glm::vec2 positions[nButtons]{
			glm::vec2(SCREEN_WIDTH / 2 - 256, SCREEN_HEIGHT / 2 - 100),
			glm::vec2(SCREEN_WIDTH / 2 - 256, SCREEN_HEIGHT / 2 + 50),
			glm::vec2(SCREEN_WIDTH / 2 - 256, SCREEN_HEIGHT / 2 + 200)
		};
		glm::ivec2 sizeButtons[nButtons]{
			glm::ivec2(512, 128),
			glm::ivec2(512, 128),
			glm::ivec2(512, 128)
		};
		glm::vec2 relation[nButtons]{
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f)
		};
		menu.loadMenu(sprites, positions, sizeButtons, relation, nButtons, true);
		menu.addImage("images/logo.png", glm::vec2(700, 300), glm::vec2(1.f, 1.f), glm::vec2(SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 - 400));
		menu.addBackground("images/backgrounds/MainMenu.png", 3);
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
			glm::vec2(SCREEN_WIDTH / 2 - 256, SCREEN_HEIGHT / 2 - 150),
			glm::vec2(SCREEN_WIDTH / 2 - 256, SCREEN_HEIGHT / 2 + 100),
			glm::vec2(15, SCREEN_HEIGHT - 80)
		};
		glm::ivec2 sizeButtons[nButtons]{
			glm::ivec2(512, 128),
			glm::ivec2(512, 128),
			glm::ivec2(128, 64)
		};
		glm::vec2 relation[nButtons]{
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f)
		};
		menu.loadMenu(sprites, positions, sizeButtons, relation, nButtons, true);
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
			glm::vec2(15, SCREEN_HEIGHT - 80)
		};
		glm::ivec2 sizeButtons[nButtons]{
			glm::ivec2(128, 64)
		};
		glm::vec2 relation[nButtons]{
			glm::vec2(1.f, 1.f / 4.f)
		};
		menu.loadMenu(sprites, positions, sizeButtons, relation, nButtons, true);
		menu.addBackground("images/backgrounds/Instructions.png", 1);
		break;
	}
	case CREDITS:
	{
		const int nButtons = 1;
		string sprites[nButtons]{
			"images/buttons/BackButton.png"
		};
		glm::vec2 positions[nButtons]{
			glm::vec2(15, SCREEN_HEIGHT - 80)
		};
		glm::ivec2 sizeButtons[nButtons]{
			glm::ivec2(128, 64)
		};
		glm::vec2 relation[nButtons]{
			glm::vec2(1.f, 1.f / 4.f)
		};
		menu.loadMenu(sprites, positions, sizeButtons, relation, nButtons, true);
		menu.addBackground("images/backgrounds/Credits.png", 1);
		break;
	}
	case PAUSE:
	{
		const int nButtons = 2;
		string sprites[nButtons]{
			"images/buttons/ResumeButton.png",
			"images/buttons/ExitButton.png"
		};
		glm::vec2 positions[nButtons]{
			glm::vec2(SCREEN_WIDTH / 2 - 256, SCREEN_HEIGHT / 2 - 150),
			glm::vec2(SCREEN_WIDTH / 2 - 256, SCREEN_HEIGHT / 2 + 100)
		};
		glm::ivec2 sizeButtons[nButtons]{
			glm::ivec2(512, 128),
			glm::ivec2(512, 128)
		};
		glm::vec2 relation[nButtons]{
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f)
		};
		menu.loadMenu(sprites, positions, sizeButtons, relation, nButtons, false);
		break;
	}
	case ENDSCREEN:
	{
		const int nButtons = 2;
		string sprites[nButtons]{
			"images/buttons/PlayAgainButton.png",
			"images/buttons/ExitButton.png"
		};
		glm::vec2 positions[nButtons]{
			glm::vec2(SCREEN_WIDTH / 2 - 256, SCREEN_HEIGHT / 2 - 50),
			glm::vec2(SCREEN_WIDTH / 2 - 256, SCREEN_HEIGHT / 2 + 200)
		};
		glm::ivec2 sizeButtons[nButtons]{
			glm::ivec2(512, 128),
			glm::ivec2(512, 128)
		};
		glm::vec2 relation[nButtons]{
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f)
		};
		menu.loadMenu(sprites, positions, sizeButtons, relation, nButtons, false);
		break;
	}
	}
}

bool Game::getCanInvertGravity() {
	return canInvertGravity;
}

void Game::setCanInvertGravity(bool b) {
	canInvertGravity = b;
}