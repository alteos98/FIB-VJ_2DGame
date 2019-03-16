#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Level.h"
#include "Game.h"

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 10
#define INIT_PLAYER_Y_TILES 20

#define N_ENEMIES11 0
#define N_ENEMIES12 0
#define N_ENEMIES13 3
#define N_ENEMIES14 2
#define N_ENEMIES15 1

#define N_ENEMIES21 1
#define N_ENEMIES22 1
#define N_ENEMIES23 1
#define N_ENEMIES24 1
#define N_ENEMIES25 1

Level::Level()
{
	map = NULL;
	player = NULL;
	for (unsigned int i = 0; i < enemy.size(); ++i) {
		enemy[i] = NULL;
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
}

void Level::init(int difficulty)
{
	if (difficulty == 1) {
		addressActualMap = "levels/level11.txt";
		actualMap = 11;
		posPlayer = glm::vec2(300, 200);
	}
		
	else if (difficulty == 2) {
		addressActualMap = "levels/level21.txt";
		actualMap = 21;
		posPlayer = glm::vec2(200, 200);
	}

	initShaders();
	player = new Player();
	isOnFloor = true;
	this->difficulty = difficulty;

	b = new Button;
	b->init(
		glm::ivec2(SCREEN_X, SCREEN_Y),
		texProgram,
		glm::ivec2(64, 64),
		glm::vec2(1.f, 1.f / 4.f),
		"images/buttons/PauseButton.png"
	);
	b->setPosition(glm::vec2(SCREEN_WIDTH - 90, 20));

	load();
}

void Level::load() {
	loadMap();
	loadPlayer();
	enemy.clear();
	loadEnemies();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Level::loadMap() {
	map = TileMap::createTileMap(addressActualMap, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
}

void Level::loadPlayer() {
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, isOnFloor);
	player->setPosition(posPlayer);
	player->setTileMap(map);
}

void Level::loadEnemies() {
	if (difficulty == 1) { // easy
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
				glm::ivec2(365, 370),
				glm::ivec2(790, 500)
			};
			glm::ivec2 posFinal[N_ENEMIES14]{
				glm::ivec2(790, 370),
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
		}
	}
	else { // hard
		switch (actualMap) {
		case 21: {
			glm::vec2 relation[N_ENEMIES21]{
				glm::vec2(1.f, 1.f / 4.f)
			};
			string nameImage[N_ENEMIES21]{
				"images/enemies/Enemy1.png"
			};
			glm::ivec2 posInicial[N_ENEMIES21]{
				glm::ivec2(0, 50)
			};
			glm::ivec2 posFinal[N_ENEMIES21]{
				glm::ivec2(50, 50)
			};
			for (int i = 0; i < N_ENEMIES21; i++) {
				Enemy* e = new Enemy;
				e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i], enemiesVelocityHard[0]);
				e->setPosition(posInicial[i]);
				e->setTileMap(map);
				enemy.push_back(e);
			}
			break;
		}
		case 22: {
			glm::vec2 relation[N_ENEMIES22]{
				glm::vec2(1.f, 1.f / 4.f)
			};
			string nameImage[N_ENEMIES22]{
				"images/enemies/Enemy1.png"
			};
			glm::ivec2 posInicial[N_ENEMIES22]{
				glm::ivec2(0, 50)
			};
			glm::ivec2 posFinal[N_ENEMIES22]{
				glm::ivec2(50, 50)
			};
			for (int i = 0; i < N_ENEMIES22; i++) {
				Enemy* e = new Enemy;
				e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i], enemiesVelocityHard[1]);
				e->setPosition(posInicial[i]);
				e->setTileMap(map);
				enemy.push_back(e);
			}
			break;
		}
		case 23: {
			glm::vec2 relation[N_ENEMIES23]{
				glm::vec2(1.f, 1.f / 4.f)
			};
			string nameImage[N_ENEMIES23]{
				"images/enemies/Enemy1.png"
			};
			glm::ivec2 posInicial[N_ENEMIES23]{
				glm::ivec2(0, 50)
			};
			glm::ivec2 posFinal[N_ENEMIES23]{
				glm::ivec2(50, 50)
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
				glm::vec2(1.f, 1.f / 4.f)
			};
			string nameImage[N_ENEMIES24]{
				"images/enemies/Enemy1.png"
			};
			glm::ivec2 posInicial[N_ENEMIES24]{
				glm::ivec2(0, 50)
			};
			glm::ivec2 posFinal[N_ENEMIES24]{
				glm::ivec2(50, 50)
			};
			for (int i = 0; i < N_ENEMIES24; i++) {
				Enemy* e = new Enemy;
				e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i], enemiesVelocityHard[3]);
				e->setPosition(posInicial[i]);
				e->setTileMap(map);
				enemy.push_back(e);
			}
			break;
		}
		case 25: {
			glm::vec2 relation[N_ENEMIES25]{
				glm::vec2(1.f, 1.f / 4.f)
			};
			string nameImage[N_ENEMIES25]{
				"images/enemies/Enemy1.png"
			};
			glm::ivec2 posInicial[N_ENEMIES25]{
				glm::ivec2(0, 50)
			};
			glm::ivec2 posFinal[N_ENEMIES25]{
				glm::ivec2(50, 50)
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
	}
	}
}

void Level::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);

	for (unsigned int i = 0; i < enemy.size(); ++i)
		enemy[i]->update(deltaTime);

	changingMapConditions();
	
	if (collisionPlayerEnemies()) {
		cout << "collision" << endl;
		// fer que el player reapareixi a l'ultim punt de guardat
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
	for (unsigned int i = 0; i < enemy.size(); ++i) {
		enemy[i]->render();
	}
	b->render();
}

// Els hi posem a tots els mapes "levelXY.txt"
// On X fa referencia a la dificultat i Y al nivell en si
void Level::nextMap () {
	if (actualMap + 1 != 16 && actualMap + 1 != 26) {
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

	if (posPlayer.x > SCREEN_WIDTH) {
		posPlayer.x = -10;
		nextMap();
		load();
		if (isOnFloor)
			player->setAnimation(1);
		else
			player->setAnimation(5);
	}
	if (posPlayer.x < -30) {
		posPlayer.x = SCREEN_WIDTH - 20;
		previousMap();
		load();
		if (isOnFloor)
			player->setAnimation(0);
		else
			player->setAnimation(4);
	}
	if (posPlayer.y >= SCREEN_HEIGHT) {
		posPlayer.y = 5;
		nextMap();
		load();
	}
	if (posPlayer.y < -25) {
		posPlayer.y = SCREEN_HEIGHT;
		previousMap();
		load();
	}
}

bool Level::buttonPress(int x, int y) {
	if ((x > b->getposB().x + SCREEN_X && x < (b->getposB().x + b->getWidth() + SCREEN_X))
		&& (y > b->getposB().y + SCREEN_Y && y < (b->getposB().y + b->getHeight() + SCREEN_Y))) {
		return true;
	}	
	return false;
}

bool Level::collisionPlayerEnemies() {
	bool b = false;
	posPlayer = player->getPosition();

	for (unsigned int i = 0; i < enemy.size() && !b; ++i) {
		if (collision(posPlayer, glm::ivec2(64, 64), enemy[i]->getPosition(), glm::ivec2(64, 64))) {
			b = true;
		}
	}
	return b;
}

bool Level::collision(glm::ivec2 &pos1, glm::ivec2 &size1, glm::ivec2 &pos2, glm::ivec2 &size2) {
	// size actualment és (64, 64) tant per player com per enemies
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