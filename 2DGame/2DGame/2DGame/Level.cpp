#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Level.h"
#include "Game.h"

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 10
#define INIT_PLAYER_Y_TILES 0

#define DURATION_ANIMATION_DEAD 200
#define INCREMENT_Y_DEAD 10

#define N_ENEMIES11 0
#define N_ENEMIES12 0
#define N_ENEMIES13 3
#define N_ENEMIES14 2
#define N_ENEMIES15 1

#define GUARDAR11 1
#define GUARDAR12 1
#define GUARDAR13 1
#define GUARDAR14 1
#define GUARDAR15 1

#define GUARDAR21 1
#define GUARDAR22 1
#define GUARDAR23 1
#define GUARDAR24 1
#define GUARDAR25 1
#define GUARDAR26 1

#define N_ENEMIES21 0
#define N_ENEMIES22 2
#define N_ENEMIES23 3
#define N_ENEMIES24 3
#define N_ENEMIES25 3
#define N_ENEMIES26 2

#define N_PLATAFORMA21 2
#define N_PLATAFORMA22 2
#define N_PLATAFORMA23 1
#define N_PLATAFORMA24 1
#define N_PLATAFORMA25 1
#define N_PLATAFORMA26 1



Level::Level()
{
	map = NULL;
	player = NULL;
	for (unsigned int i = 0; i < enemy.size(); ++i) {
		enemy[i] = NULL;
	}
	for (unsigned int i = 0; i < guardar.size(); ++i) {
		guardar[i] = NULL;
	}
	for (unsigned int i = 0; i < spikes.size(); ++i) {
		spikes[i] = NULL;
	}
	for (unsigned int i = 0; i < plataforma.size(); ++i) {
		plataforma[i] = NULL;
	}
	star = NULL;
	for (unsigned int i = 0; i < lightning.size(); ++i) {
		lightning[i] = NULL;
	}
	for (unsigned int i = 0; i < stalactites.size(); ++i) {
		stalactites[i] = NULL;
	}
}

Level::~Level()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	for (unsigned int i = 0; i < enemy.size(); ++i) {
		if (enemy[i] != NULL)
			delete enemy[i];
	}
	for (unsigned int i = 0; i < guardar.size(); ++i) {
		if (guardar[i] != NULL)
			delete guardar[i];
	}
	for (unsigned int i = 0; i < spikes.size(); ++i) {
		if (spikes[i] != NULL)
			delete spikes[i];
	}
	for (unsigned int i = 0; i < plataforma.size(); ++i) {
		if (plataforma[i] != NULL)
			delete plataforma[i];
	}
	if (star != NULL)
		delete star;
	for (unsigned int i = 0; i < lightning.size(); ++i) {
		if (lightning[i] != NULL)
			delete lightning[i];
	}
	for (unsigned int i = 0; i < stalactites.size(); ++i) {
		if (stalactites[i] != NULL)
			delete stalactites[i];
	}
}

void Level::init(int difficulty)
{
	InitPosGuardar();
	initShaders();

	if (difficulty == 1) {
		addressActualMap = "levels/level11.txt";
		actualMap = 11;
		posPlayer = posPlayerIni = glm::vec2(300, 200);
	}

	else if (difficulty == 2) {
		addressActualMap = "levels/level22.txt";
		actualMap = 22;
		posPlayer = posPlayerIni = glm::vec2(50, 50);
	}

	player = new Player;
	pauseButton = new Button;
	star = new Star;
	treasure = new Treasure;

	sizePlayer = glm::ivec2(64, 64);
	isOnFloor = true;
	ContactoPlat = false;
	collisioned = false;
	this->difficulty = difficulty;
	numGuardado = -1;

	load();
}

void Level::update(int deltaTime)
{
	cout << posPlayer.x << " " << posPlayer.y << endl;
	// Update every interactuable object
	currentTime += deltaTime;
	if (!collisioned)
		player->update(deltaTime);
	if (actualMap == 15 || actualMap == 26)
		star->update(deltaTime);
	for (unsigned int i = 0; i < enemy.size(); ++i)
		enemy[i]->update(deltaTime);
	for (unsigned int i = 0; i < guardar.size(); ++i)
		guardar[i]->update(deltaTime);
	for (unsigned int i = 0; i < plataforma.size(); ++i)
		plataforma[i]->update(deltaTime);
	for (unsigned int i = 0; i < lightning.size(); ++i)
		lightning[i]->update(deltaTime);
	for (unsigned int i = 0; i < stalactites.size(); ++i) {
		if (!stalactites[i]->getFalling() && stalactites[i]->hasToFall(posPlayer))
			stalactites[i]->setFalling(true);
		if (stalactites[i]->outOfMap())
			stalactites[i]->setFalling(false);
		stalactites[i]->update(deltaTime);
	}
	if (actualMap == 23) {
		treasure->update(deltaTime);

		if (collisionPlayerTreasure()) {
			treasure->open();
			sizePlayer = glm::ivec2(32, 32);
			player->setSize(sizePlayer);
			player->initSprite();
			player->setPosition(posPlayer);
		}
	}

	changingMapConditions();

	// Checking collisions
	if (!collisioned && (collisionPlayerEnemies() || collisionPlayerSpikes() || collisionPlayerStalactite())) {
		currentTimeCollision = currentTime;
		collisioned = true;
		player->setAnimation(8);
	}
	else if (collisioned && currentTime - currentTimeCollision >= DURATION_ANIMATION_DEAD) {
		if (numGuardado != -1) posPlayer = glm::ivec2(posicionesGuardar[numGuardado - 1].x, posicionesGuardar[numGuardado - 1].y);
		player->setPosition(glm::vec2(posPlayer.x, posPlayer.y));
		changeMap();
		player->setIsOnFloor(true);
		collisioned = false;
	}
	/*else if (collisioned) {
		if ((isOnFloor && player->getBGravity()) && (!isOnFloor && !player->getBGravity()))
			posPlayer.y = posPlayer.y + player->getFallStep() - INCREMENT_Y_DEAD;
		else if ((isOnFloor && !player->getBGravity()) && (!isOnFloor && player->getBGravity()))
			posPlayer.y = posPlayer.y - player->getFallStep() - INCREMENT_Y_DEAD;
		player->setPosition(glm::ivec2(posPlayer.x, posPlayer.y));
	}*/
	int aux = -1;
	if (collisionPlayerGuardar(aux)) {
		if (aux != -1 && numGuardado != aux) {
			numGuardado = aux;
			Actualizarllama();
		}
	}
	if (mapacambiado) { Actualizarllama(); mapacambiado = false; }

	int nump;
	/*if (collisionPlayerPlataformaLateral(nump)) {

	}
	else */if (collisionPlayerPlataforma(nump)) {
		if (!ContactoPlat) {
			if (player->getbGravity())player->setIsOnFloor(!player->getIsOnFloor());
			ContactoPlat = true;
		}
		player->setGravity(false);
		int sum = 0;
		if (player->getIsOnFloor())
			sum = -player->getFallStep();
		else sum = player->getFallStep();

		int addvx, addvy;
		addvx = plataforma[nump]->getIncrease().x;
		addvy = plataforma[nump]->getIncrease().y;

		int desfas = 0;
		if (player->getIsOnFloor()) {
			desfas = plataforma[nump]->getPosition().y - (player->getPosition().y + player->getHeight() - addvy);
			if (desfas > -10)
				desfas = abs(desfas);
			else
				desfas = 0;
		}
		else if (!player->getIsOnFloor()) {
			desfas = player->getPosition().y - (plataforma[nump]->getPosition().y + plataforma[nump]->getHeight() + addvx);
			if (desfas > -10)
				desfas = -abs(desfas);
			else
				desfas = 0;
		}

		player->setPosition(glm::vec2(float(player->getPosition().x + addvx), float(desfas + addvy + sum + player->getPosition().y)));


		if (Game::instance().getKey(' ') && Game::instance().getCanInvertGravity()) {
			player->setGravity(true);
			Game::instance().setCanInvertGravity(false);
		}
	}
	else ContactoPlat = false;

	if (collisionPlayerLightning()) {
		isOnFloor = player->getIsOnFloor();
		player->setIsOnFloor(!isOnFloor);
	}
}

void Level::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	map->render();
	player->render();
	for (unsigned int i = 0; i < enemy.size(); ++i)
		enemy[i]->render();
	for (unsigned int i = 0; i < guardar.size(); ++i)
		guardar[i]->render();
	for (unsigned int i = 0; i < spikes.size(); ++i)
		spikes[i]->render();
	for (unsigned int i = 0; i < lightning.size(); ++i)
		lightning[i]->render();
	for (unsigned int i = 0; i < stalactites.size(); ++i) {
		if (!stalactites[i]->outOfMap())
			stalactites[i]->render();
	}
	for (unsigned int i = 0; i < plataforma.size(); ++i) {
		plataforma[i]->render();
	}
	if (actualMap == 15 || actualMap == 26)
		star->render();
	if (actualMap == 23)
		treasure->render();
	pauseButton->render();
}


// LOAD

void Level::load() {
	enemy.clear();
	plataforma.clear();
	guardar.clear();
	spikes.clear();
	lightning.clear();
	stalactites.clear();

	loadMap();
	loadPlayer();
	loadEnemies();
	loadPlataforma();
	loadGuardar();
	loadSpikes();
	loadStar();
	loadLightning();
	loadStalactites();
	loadTresure();
	loadPauseButton();

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Level::loadMap() {
	mapacambiado = true;
	map = TileMap::createTileMap(addressActualMap, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
}

void Level::loadSpikes() {
	if (actualMap == 12) {
		for (unsigned int i = 0; i < 5; ++i) {
			Spike* spike = new Spike();
			glm::ivec2 spikeSize = glm::ivec2(64, 64);
			spike->init(glm::ivec2(415 + i * (spikeSize.x - 16), SCREEN_HEIGHT - 64), texProgram, spikeSize, false);
			spikes.push_back(spike);
		}
	}
	else if (actualMap == 24) {
		for (unsigned int i = 0; i < 17; ++i) {
			Spike* spike = new Spike();
			glm::ivec2 spikeSize = glm::ivec2(64, 64);
			spike->init(glm::ivec2(125 + i * (spikeSize.x - 16), SCREEN_HEIGHT - 92), texProgram, spikeSize, false);
			spikes.push_back(spike);
		}
		for (unsigned int i = 0; i < 18; ++i) {
			Spike* spike = new Spike();
			glm::ivec2 spikeSize = glm::ivec2(64, 64);
			spike->init(glm::ivec2(120 + i * (spikeSize.x - 16), 32), texProgram, spikeSize, true);
			spikes.push_back(spike);
		}
	}
	else if (actualMap == 25) {
		for (unsigned int i = 0; i < 15; ++i) {
			if (i % 3 != 0) {
				Spike* spike = new Spike();
				glm::ivec2 spikeSize = glm::ivec2(64, 64);
				spike->init(glm::ivec2(160 + i * (spikeSize.x - 16), SCREEN_HEIGHT - 256), texProgram, spikeSize, true);
				spikes.push_back(spike);
			}
		}
	}
}

void Level::loadPlayer() {
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, sizePlayer, isOnFloor);
	player->setPosition(posPlayer);
	player->setTileMap(map);
}

void Level::loadEnemies() {
	switch (actualMap) {
	case 13: {
		glm::vec2 relation[N_ENEMIES13]{
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES13]{
			"images/enemies/Ball.png",
			"images/enemies/Ball.png",
			"images/enemies/Ball.png"
		};
		glm::ivec2 posInicial[N_ENEMIES13]{
			glm::ivec2(255, 175),
			glm::ivec2(510, 605),
			glm::ivec2(770, 175)
		};
		glm::ivec2 posFinal[N_ENEMIES13]{
			glm::ivec2(255, 660),
			glm::ivec2(510, 110),
			glm::ivec2(770, 660)
		};
		for (int i = 0; i < N_ENEMIES13; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i], enemiesVelocityEasy[2]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}
	case 14: {
		glm::vec2 relation[N_ENEMIES14]{
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES14]{
			"images/enemies/Bear.png",
			"images/enemies/Bear.png"
		};
		glm::ivec2 posInicial[N_ENEMIES14]{
			glm::ivec2(365, 360),
			glm::ivec2(790, 500)
		};
		glm::ivec2 posFinal[N_ENEMIES14]{
			glm::ivec2(790, 360),
			glm::ivec2(365, 500)
		};
		for (int i = 0; i < N_ENEMIES14; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i], enemiesVelocityEasy[3]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}
	case 15: {
		glm::vec2 relation[N_ENEMIES15]{
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES15]{
			"images/enemies/Dinosaur.png"
		};
		glm::ivec2 posInicial[N_ENEMIES15]{
			glm::ivec2(560, 150)
		};
		glm::ivec2 posFinal[N_ENEMIES15]{
			glm::ivec2(560, 690)
		};
		for (int i = 0; i < N_ENEMIES15; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i], enemiesVelocityEasy[4]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}
	/*case 22: {
		glm::vec2 relation[N_ENEMIES22]{
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES22]{
			"images/enemies/Llama.png",
			"images/enemies/Llama.png"
		};
		glm::ivec2 posInicial[N_ENEMIES22]{
			glm::ivec2(100, SCREEN_HEIGHT - 500),
			glm::ivec2(SCREEN_WIDTH - 500, SCREEN_HEIGHT - 300)
		};
		glm::ivec2 posFinal[N_ENEMIES22]{
			glm::ivec2(SCREEN_WIDTH - 500, SCREEN_HEIGHT - 500),
			glm::ivec2(100, SCREEN_HEIGHT - 300)
		};
		for (int i = 0; i < N_ENEMIES22; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i], enemiesVelocityHard[1]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}*/
	case 23: {
		glm::vec2 relation[N_ENEMIES23]{
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES23]{
			"images/enemies/Star.png",
			"images/enemies/Star.png",
			"images/enemies/Star.png"
		};
		glm::ivec2 posInicial[N_ENEMIES23]{
			glm::ivec2(400, SCREEN_HEIGHT - 135),
			glm::ivec2(690, SCREEN_HEIGHT - 335),
			glm::ivec2(SCREEN_WIDTH - 180, 100)
		};
		glm::ivec2 posFinal[N_ENEMIES23]{
			glm::ivec2(400, SCREEN_HEIGHT - 335),
			glm::ivec2(690, SCREEN_HEIGHT - 135),
			glm::ivec2(SCREEN_WIDTH - 180, SCREEN_HEIGHT - 150)
		};
		for (int i = 0; i < N_ENEMIES23; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i], enemiesVelocityHard[2]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}
	case 24: {
		glm::vec2 relation[N_ENEMIES24]{
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES24]{
			"images/enemies/Romb.png",
			"images/enemies/Romb.png",
			"images/enemies/Romb.png"
		};
		glm::ivec2 posInicial[N_ENEMIES24]{
			glm::ivec2(200, 230),
			glm::ivec2(SCREEN_WIDTH - 200, 360),
			glm::ivec2(200, 490)
		};
		glm::ivec2 posFinal[N_ENEMIES24]{
			glm::ivec2(SCREEN_WIDTH - 200, 230),
			glm::ivec2(200, 360),
			glm::ivec2(SCREEN_WIDTH - 200, 490)
		};
		for (int i = 0; i < N_ENEMIES24; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i], enemiesVelocityHard[4]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}
	case 25: {
		glm::vec2 relation[N_ENEMIES25]{
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES25]{
			"images/enemies/Duck.png",
			"images/enemies/Llama.png",
			"images/enemies/Rabbit.png"
		};
		glm::ivec2 posInicial[N_ENEMIES25]{
			glm::ivec2(305, 50),
			glm::ivec2(495, 470),
			glm::ivec2(690, 50)
		};
		glm::ivec2 posFinal[N_ENEMIES25]{
			glm::ivec2(305, 470),
			glm::ivec2(495, 50),
			glm::ivec2(690, 470)
		};
		for (int i = 0; i < N_ENEMIES25; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i], enemiesVelocityHard[4]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}
	case 26: {
		glm::vec2 relation[N_ENEMIES26]{
			glm::vec2(1.f, 1.f / 4.f),
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES26]{
			"images/enemies/Heart.png",
			"images/enemies/Heart.png"
		};
		glm::ivec2 posInicial[N_ENEMIES26]{
			glm::ivec2(450, 40),
			glm::ivec2(700, 40)
		};
		glm::ivec2 posFinal[N_ENEMIES26]{
			glm::ivec2(450, 220),
			glm::ivec2(700, 220)
		};
		for (int i = 0; i < N_ENEMIES26; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i], enemiesVelocityHard[5]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}
	}
}

void Level::loadPlataforma() {
	if (difficulty == 2) { // easy
		switch (actualMap) {
		case 22: {
			glm::vec2 relation[N_PLATAFORMA22]{
				glm::vec2(1.f, 1.f),
				glm::vec2(1.f, 1.f)
			};
			string nameImage[N_PLATAFORMA22]{
				"images/plataforma/nube1.png",
				"images/plataforma/nube1.png"
			};
			glm::ivec2 posInicial[N_PLATAFORMA22]{
				glm::ivec2(32 * 8, 32 * 7),
				glm::ivec2(32 * 8, 32 * 9)
			};
			glm::ivec2 posFinal[N_PLATAFORMA22]{
				glm::ivec2(32 * 16, 32 * 7),
				glm::ivec2(32 * 8, 32 * 18)
			};
			for (int i = 0; i < N_PLATAFORMA22; i++) {
				Plataforma* e = new Plataforma;
				e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i], plataformaVelocityHard[2]);
				e->setPosition(posInicial[i]);
				e->setTileMap(map);
				plataforma.push_back(e);
			}
			break;
		}
		}
	}
}

void Level::loadGuardar() {
	switch (actualMap) {
	case 11: {
		int id = 1;
		glm::ivec2 posIni[GUARDAR11]{
			glm::ivec2(posicionesGuardar[id - 1].x, posicionesGuardar[id - 1].y)

		};
		for (int i = 0; i < GUARDAR11; i++) {
			Guardar* g = new Guardar;
			g->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(64, 64), id);
			g->setPosition(posIni[i]);
			g->setTileMap(map);
			guardar.push_back(g);
		}
		break;
	}
	case 12: {
		int id = 2;
		glm::ivec2 posIni[GUARDAR12]{
			glm::ivec2(posicionesGuardar[id - 1].x, posicionesGuardar[id - 1].y)
		};
		for (int i = 0; i < GUARDAR12; i++) {
			Guardar* g = new Guardar;
			g->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(64, 64), id);
			g->setPosition(posIni[i]);
			g->setTileMap(map);
			guardar.push_back(g);
		}
		break;
	}
	case 13: {
		int id = 3;
		glm::ivec2 posIni[GUARDAR13]{
			glm::ivec2(posicionesGuardar[id - 1].x, posicionesGuardar[id - 1].y)
		};
		for (int i = 0; i < GUARDAR13; i++) {
			Guardar* g = new Guardar;
			g->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(64, 64), id);
			g->setPosition(posIni[i]);
			g->setTileMap(map);
			guardar.push_back(g);
		}
		break;
	}
	case 14: {
		int id = 4;
		glm::ivec2 posIni[GUARDAR14]{
			glm::ivec2(posicionesGuardar[id - 1].x, posicionesGuardar[id - 1].y)
		};
		for (int i = 0; i < GUARDAR14; i++) {
			Guardar* g = new Guardar;
			g->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(64, 64), id);
			g->setPosition(posIni[i]);
			g->setTileMap(map);
			guardar.push_back(g);
		}
		break;
	}
	case 15: {
		int id = 5;
		glm::ivec2 posIni[GUARDAR15]{
			glm::ivec2(posicionesGuardar[id - 1].x, posicionesGuardar[id - 1].y)
		};
		for (int i = 0; i < GUARDAR15; i++) {
			Guardar* g = new Guardar;
			g->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(64, 64), id);
			g->setPosition(posIni[i]);
			g->setTileMap(map);
			guardar.push_back(g);
		}
		break;
	}
	case 21: {
		int id = 6;
		glm::ivec2 posIni[GUARDAR21]{
			glm::ivec2(posicionesGuardar[id - 1].x, posicionesGuardar[id - 1].y)
		};
		for (int i = 0; i < GUARDAR21; i++) {
			Guardar* g = new Guardar;
			g->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(64, 64), id);
			g->setPosition(posIni[i]);
			g->setTileMap(map);
			guardar.push_back(g);
		}
		break;
	}
	case 22: {
		int id = 7;
		glm::ivec2 posIni[GUARDAR22]{
			glm::ivec2(posicionesGuardar[id - 1].x, posicionesGuardar[id - 1].y)
		};
		for (int i = 0; i < GUARDAR22; i++) {
			Guardar* g = new Guardar;
			g->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(64, 64), id);
			g->setPosition(posIni[i]);
			g->setTileMap(map);
			guardar.push_back(g);
		}
		break;
	}
	case 23: {
		int id = 8;
		glm::ivec2 posIni[GUARDAR23]{
			glm::ivec2(posicionesGuardar[id - 1].x, posicionesGuardar[id - 1].y)
		};
		for (int i = 0; i < GUARDAR23; i++) {
			Guardar* g = new Guardar;
			g->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(64, 64), id);
			g->setPosition(posIni[i]);
			g->setTileMap(map);
			guardar.push_back(g);
		}
		break;
	}
	case 24: {
		int id = 9;
		glm::ivec2 posIni[GUARDAR24]{
			glm::ivec2(posicionesGuardar[id - 1].x, posicionesGuardar[id - 1].y)
		};
		for (int i = 0; i < GUARDAR24; i++) {
			Guardar* g = new Guardar;
			g->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(64, 64), id);
			g->setPosition(posIni[i]);
			g->setTileMap(map);
			guardar.push_back(g);
		}
		break;
	}
	case 25: {
		int id = 10;
		glm::ivec2 posIni[GUARDAR25]{
			glm::ivec2(posicionesGuardar[id - 1].x, posicionesGuardar[id - 1].y)
		};
		for (int i = 0; i < GUARDAR25; i++) {
			Guardar* g = new Guardar;
			g->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(64, 64), id);
			g->setPosition(posIni[i]);
			g->setTileMap(map);
			guardar.push_back(g);
		}
		break;
	}
	case 26: {
		int id = 11;
		glm::ivec2 posIni[GUARDAR26]{
			glm::ivec2(posicionesGuardar[id - 1].x, posicionesGuardar[id - 1].y)
		};
		for (int i = 0; i < GUARDAR26; i++) {
			Guardar* g = new Guardar;
			g->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(64, 64), id);
			g->setPosition(posIni[i]);
			g->setTileMap(map);
			guardar.push_back(g);
		}
		break;
	}
	}
}

void Level::loadStar() {
	if (actualMap == 15) {
		glm::ivec2 starSize = glm::ivec2(64, 64);
		star->init(glm::ivec2(SCREEN_WIDTH - 128, SCREEN_HEIGHT - 135), texProgram, starSize);
	}
	else if (actualMap == 26) {
		glm::ivec2 starSize = glm::ivec2(64, 64);
		star->init(glm::ivec2(SCREEN_WIDTH - 128, 210), texProgram, starSize);
	}
}

void Level::loadLightning() {
	if (actualMap == 21) {
		Lightning* l = new Lightning;
		glm::ivec2 lightningPos = glm::ivec2(SCREEN_WIDTH - 400, SCREEN_HEIGHT - 300);
		glm::ivec2 lightningSize = glm::ivec2(256, 64);
		l->init(lightningPos, texProgram, lightningSize, false);
		lightning.push_back(l);
	}
	else if (actualMap == 22) {
		Lightning* l = new Lightning;
		glm::ivec2 lightningPos = glm::ivec2(SCREEN_WIDTH - 350, SCREEN_HEIGHT - 300);
		glm::ivec2 lightningSize = glm::ivec2(128, 64);
		l->init(lightningPos, texProgram, lightningSize, false);
		lightning.push_back(l);
	}
	else if (actualMap == 24) {
		glm::ivec2 lightningPos, lightningSize;
		for (unsigned int i = 0; i < 3; ++i) {
			Lightning* l = new Lightning;
			if (i == 0) {
				lightningSize = glm::ivec2(256, 64);
				lightningPos = glm::ivec2(200, 100);
			}
			else if (i == 1) {
				lightningSize = glm::ivec2(256, 64);
				lightningPos = glm::ivec2(450, 650);
			}
			else if (i == 2) {
				lightningSize = glm::ivec2(256, 64);
				lightningPos = glm::ivec2(700, 100);
			}
			l->init(lightningPos, texProgram, lightningSize, false);
			lightning.push_back(l);
		}
	}
}

void Level::loadStalactites() {
	if (actualMap == 15) {
		Stalactite* stalactite = new Stalactite;
		glm::ivec2 stalactitePos = glm::ivec2(300, 128);
		glm::ivec2 stalactiteSize = glm::ivec2(64, 128);
		stalactite->init(stalactitePos, texProgram, stalactiteSize);
		stalactite->setMargin(50, SCREEN_HEIGHT);
		stalactite->setFallingVelocity(15);
		stalactites.push_back(stalactite);
	}
	else if (actualMap == 25) {
		Stalactite* stalactite = new Stalactite;
		glm::ivec2 stalactitePos = glm::ivec2(SCREEN_WIDTH - 100, 128);
		glm::ivec2 stalactiteSize = glm::ivec2(64, 128);
		stalactite->init(stalactitePos, texProgram, stalactiteSize);
		stalactite->setMargin(200, SCREEN_HEIGHT);
		stalactite->setFallingVelocity(15);
		stalactites.push_back(stalactite);

		for (unsigned int i = 0; i < 5; ++i) {
			stalactite = new Stalactite;
			stalactitePos = glm::ivec2(160 + 143 * i, SCREEN_HEIGHT - 256);
			stalactiteSize = glm::ivec2(64, 64);
			stalactite->init(stalactitePos, texProgram, stalactiteSize);
			stalactite->setMargin(30, SCREEN_HEIGHT);
			stalactite->setFallingVelocity(15);
			stalactites.push_back(stalactite);
		}

		for (unsigned int i = 0; i < 4; ++i) {
			stalactite = new Stalactite;
			stalactitePos = glm::ivec2(208 + 192 * i, 224);
			stalactiteSize = glm::ivec2(64, 64);
			stalactite->init(stalactitePos, texProgram, stalactiteSize);
			stalactite->setMargin(30, 300);
			stalactite->setFallingVelocity(15);
			stalactites.push_back(stalactite);
		}
	}
}

void Level::loadTresure() {
	if (actualMap == 23) {
		glm::ivec2 treasurePos = glm::ivec2(SCREEN_WIDTH - 650, 260);
		glm::ivec2 treasureSize = glm::ivec2(64, 64);
		treasure->init(treasurePos, texProgram, treasureSize);
	}
}

void Level::loadPauseButton() {
	pauseButton->init(
		glm::ivec2(SCREEN_X, SCREEN_Y),
		texProgram,
		glm::ivec2(64, 64),
		glm::vec2(1.f, 1.f / 4.f),
		"images/buttons/PauseButton.png"
	);
	pauseButton->setPosition(glm::vec2(SCREEN_WIDTH - 90, 20));
}


// MAP

void Level::setMap(int newMap) {
	this->actualMap = newMap;
	this->addressActualMap = "levels/level" + to_string(newMap) + ".txt";
}

void Level::nextMap() {
	if (actualMap + 1 != 16 && actualMap + 1 != 27) {
		int numberOfTheNewMap = int(addressActualMap[13]) + 1;
		addressActualMap[13] = char(numberOfTheNewMap);
		actualMap++;
	}
}

void Level::previousMap() {
	if (actualMap - 1 != 10 && actualMap - 1 != 20) {
		int numberOfTheNewMap = int(addressActualMap[13]) - 1;
		addressActualMap[13] = char(numberOfTheNewMap);
		actualMap--;
	}
}

void Level::changingMapConditions() {
	isOnFloor = player->getIsOnFloor();
	posPlayer = player->getPosition();

	if (actualMap == 11 || actualMap == 12 || actualMap == 13 || actualMap == 14 || actualMap == 15) {
		if (posPlayer.x > SCREEN_WIDTH) {
			posPlayer.x = -32;
			nextMap();
			load();
			if (isOnFloor)
				player->setAnimation(1);
			else
				player->setAnimation(5);
		}
		else if (posPlayer.x < -64) {
			posPlayer.x = SCREEN_WIDTH - 32;
			previousMap();
			load();
			if (isOnFloor)
				player->setAnimation(0);
			else
				player->setAnimation(4);
		}
	}
	else if (actualMap == 21) {
		if (posPlayer.x < -64) {
			posPlayer.x = SCREEN_WIDTH - 32;
			setMap(22);
			load();
			if (isOnFloor)
				player->setAnimation(0);
			else
				player->setAnimation(4);
		}
	}
	else if (actualMap == 22) {
		if (posPlayer.y >= SCREEN_HEIGHT + 20) {
			posPlayer.y = 0;
			if (!isOnFloor)
				isOnFloor = !isOnFloor;
			setMap(23);
			load();
		}
		else if (posPlayer.x > SCREEN_WIDTH) {
			posPlayer.x = -32;
			setMap(21);
			load();
			if (isOnFloor)
				player->setAnimation(1);
			else
				player->setAnimation(5);
		}
	}
	else if (actualMap == 23) {
		if (posPlayer.x > SCREEN_WIDTH) {
			posPlayer.x = -32;
			setMap(24);
			load();
			if (isOnFloor)
				player->setAnimation(1);
			else
				player->setAnimation(5);
		}
		else if (posPlayer.y < -128) {
			posPlayer.y = SCREEN_HEIGHT;
			if (isOnFloor)
				isOnFloor = !isOnFloor;
			setMap(22);
			load();
		}
	}
	else if (actualMap == 24) {
		if (posPlayer.x > SCREEN_WIDTH) {
			posPlayer.x = -32;
			setMap(25);
			load();
			if (isOnFloor)
				player->setAnimation(1);
			else
				player->setAnimation(5);
		}
		else if (posPlayer.x < -64) {
			posPlayer.x = SCREEN_WIDTH - 32;
			setMap(23);
			load();
			if (isOnFloor)
				player->setAnimation(0);
			else
				player->setAnimation(4);
		}
	}
	else if (actualMap == 25) {
		if (posPlayer.y < -128) {
			posPlayer.y = SCREEN_HEIGHT;
			if (isOnFloor)
				isOnFloor = !isOnFloor;
			setMap(26);
			load();
		}
		else if (posPlayer.x < -64) {
			posPlayer.x = SCREEN_WIDTH - 32;
			setMap(24);
			load();
			if (isOnFloor)
				player->setAnimation(0);
			else
				player->setAnimation(4);
		}
	}
	else if (actualMap == 26) {
		if (posPlayer.y >= SCREEN_HEIGHT + 20) {
			posPlayer.y = 0;
			if (!isOnFloor)
				isOnFloor = !isOnFloor;
			setMap(25);
			load();
		}
	}
}

void Level::changeMap()
{
	if (numGuardado >= 0) {
		addressActualMap[13] = char(posicionesGuardar[numGuardado - 1].z) + '0';
		actualMap = (addressActualMap[12] - '0') * 10 + posicionesGuardar[numGuardado - 1].z;
	}
	else {
		if (difficulty == 1) {
			addressActualMap = "levels/level11.txt";
			actualMap = 11;
		}
		else if (difficulty == 2) {
			addressActualMap = "levels/level22.txt";
			actualMap = 22;
		}
		posPlayer = posPlayerIni;
	}
	load();
	if (isOnFloor)
		player->setAnimation(0);
	else
		player->setAnimation(4);
}

void Level::Actualizarllama() {
	if (numGuardado != -1) {
		for (unsigned int i = 0; i < guardar.size(); ++i) {
			if (numGuardado == guardar[i]->getID()) {
				guardar[i]->Cambiar_llama(true);
			}
			else guardar[i]->Cambiar_llama(false);
		}
	}
}


// COLLISION

bool Level::collisionPlayerEnemies() {
	bool b = false;
	posPlayer = player->getPosition();

	for (unsigned int i = 0; i < enemy.size() && !b; ++i) {
		if (collision(posPlayer, glm::ivec2(player->getWidth(), player->getHeight()), enemy[i]->getPosition(), glm::ivec2(enemy[i]->getWidth(), enemy[i]->getHeight()))) {
			b = true;
		}
	}
	return b;
}

bool Level::collisionPlayerPlataforma(int& PlataformaAct) {
	bool b = false;
	posPlayer = player->getPosition();

	for (unsigned int i = 0; i < plataforma.size() && !b; ++i) {
		if (collision(posPlayer, glm::ivec2(player->getWidth(), player->getHeight() - 5), plataforma[i]->getPosition(), glm::ivec2(plataforma[i]->getWidth(), plataforma[i]->getHeight() - 5))) {
			b = true;
			PlataformaAct = i;
		}
	}
	return b;

}

bool Level::collisionPlayerPlataformaLateral(int& PlataformaAct) {
	posPlayer = player->getPosition();

	for (unsigned int i = 0; i < plataforma.size(); ++i) {
		if (collisionLateral(posPlayer, glm::ivec2(player->getWidth(), player->getHeight()), plataforma[i]->getPosition(), glm::ivec2(plataforma[i]->getWidth(), plataforma[i]->getHeight()))) {
			return true;
		}
	}
	return false;

}

bool Level::collisionPlayerGuardar(int & GuardadoActual) {
	bool b = false;
	posPlayer = player->getPosition();

	for (unsigned int i = 0; i < guardar.size() && !b; ++i) {
		if (collision(posPlayer, glm::ivec2(player->getWidth(), player->getHeight()), guardar[i]->getposG(), glm::ivec2(64, 128))) {
			b = true;
			GuardadoActual = guardar[i]->getID();
			cout << guardar[i]->getID();
		}
	}
	return b;
}

bool Level::collisionPlayerSpikes() {
	bool b = false;

	for (unsigned int i = 0; i < spikes.size() && !b; ++i) {
		if (collision(player->getPosition(), glm::ivec2(player->getWidth(), player->getHeight()), spikes[i]->getPosition(), glm::ivec2(spikes[i]->getWidth(), spikes[i]->getHeight()))) {
			b = true;
		}
	}
	return b;
}

bool Level::collisionPlayerStar() {
	bool b = false;

	if (collision(player->getPosition(), glm::ivec2(player->getWidth(), player->getHeight()), star->getPosition(), glm::ivec2(star->getWidth(), star->getHeight()))) {
		b = true;
	}
	return b;
}

bool Level::collisionPlayerLightning() {
	bool b = false;

	for (unsigned int i = 0; i < lightning.size() && !b; ++i) {
		glm::ivec2 lightiningPosition = lightning[i]->getPosition();
		lightiningPosition.y = lightiningPosition.y + lightning[i]->getHeight() / 2;
		if (collision(player->getPosition(), glm::ivec2(player->getWidth(), player->getHeight()), lightiningPosition, glm::ivec2(lightning[i]->getWidth(), 1))) {
			b = true;
		}
	}
	return b;
}

bool Level::collisionPlayerStalactite() {
	bool b = false;

	for (unsigned int i = 0; i < stalactites.size() && !b; ++i) {
		if (collision(player->getPosition(), glm::ivec2(player->getWidth(), player->getHeight()), stalactites[i]->getPosition(), glm::ivec2(stalactites[i]->getWidth(), stalactites[i]->getHeight()))) {
			b = true;
		}
	}
	return b;
}

bool Level::collisionPlayerTreasure() {
	bool b = false;

	if (collision(player->getPosition(), glm::ivec2(player->getWidth(), player->getHeight()), treasure->getPosition(), glm::ivec2(treasure->getWidth(), treasure->getHeight()))) {
		b = true;
	}
	return b;
}

bool Level::collision(glm::ivec2 &pos1, glm::ivec2 &size1, glm::ivec2 &pos2, glm::ivec2 &size2) {
	// size actualment �s (64, 64) tant per player com per enemies
	int x0_1, x_1, y0_1, y_1, x0_2, x_2, y0_2, y_2;
	x0_1 = pos1.x; x_1 = pos1.x + size1.x;
	y0_1 = pos1.y; y_1 = pos1.y + size1.y;
	x0_2 = pos2.x; x_2 = pos2.x + size2.x;
	y0_2 = pos2.y; y_2 = pos2.y + size2.y;

	if (!(x0_1 > x_2) && !(x0_2 > x_1) && !(y0_1 > y_2) && !(y0_2 > y_1)) {
		return true;
	}
	return false;
}

bool Level::collisionLateral(glm::ivec2 &pos1, glm::ivec2 &size1, glm::ivec2 &pos2, glm::ivec2 &size2) {
	int x0_1, x_1, y0_1, y_1, x0_2, x_2, y0_2, y_2;
	x0_1 = pos1.x; x_1 = pos1.x + size1.x;
	y0_1 = pos1.y; y_1 = pos1.y + size1.y;
	x0_2 = pos2.x; x_2 = pos2.x + size2.x;
	y0_2 = pos2.y; y_2 = pos2.y + size2.y;

	if ((x_1 >= x0_2 && x0_1 <= x0_2) || (x_2 >= x0_1 && x_2 <= x0_1))
		return true;
	return false;
}


// GETTERS

int Level::getActualMap() {
	return actualMap;
}

int Level::getDifficulty() {
	return difficulty;
}


// SETTERS

void Level::setPlayerPosition(glm::ivec2 newPlayerPos) {
	this->posPlayer = newPlayerPos;
}


// OTHER

void Level::InitPosGuardar() {
	// El tercer elemento es el mapa en el que es la posicion
	vector<glm::ivec3> g(11);

	// Easy mode
	g[0] = glm::ivec3(780, 482, 1);
	g[1] = glm::ivec3(850, 482, 2);
	g[2] = glm::ivec3(64, 482, 3);
	g[3] = glm::ivec3(50, 162, 4);
	g[4] = glm::ivec3(50, 162, 5);

	// Hard mode
	g[5] = glm::ivec3(965, 418, 1);
	g[6] = glm::ivec3(50, 65, 2);
	g[7] = glm::ivec3(36, 418, 3);
	g[8] = glm::ivec3(45, 482, 4);
	g[9] = glm::ivec3(50, 674, 5);
	g[10] = glm::ivec3(45, 418, 6);

	posicionesGuardar = g;
}

bool Level::buttonPress(int x, int y) {
	if ((x > pauseButton->getposB().x + SCREEN_X && x < (pauseButton->getposB().x + pauseButton->getWidth() + SCREEN_X))
		&& (y > pauseButton->getposB().y + SCREEN_Y && y < (pauseButton->getposB().y + pauseButton->getHeight() + SCREEN_Y))) {
		return true;
	}
	return false;
}

void Level::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}