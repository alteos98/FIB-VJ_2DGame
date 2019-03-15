#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Level.h"
#include "Game.h"

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 10
#define INIT_PLAYER_Y_TILES 20

#define N_ENEMIES1 1
#define N_ENEMIES2 1
#define N_ENEMIES3 1
#define N_ENEMIES4 1
#define N_ENEMIES5 1
#define N_ENEMIES6 1
#define N_ENEMIES7 1
#define N_ENEMIES8 1
#define N_ENEMIES9 1
#define N_ENEMIES10 1

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
		posPlayer = glm::vec2(10*16, 20*16);
	}
		
	else if (difficulty == 2)
		addressActualMap = "levels/level21.txt";

	player = new Player();
	isOnFloor = true;
	load();
}

void Level::load() {
	initShaders();
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
	switch (actualMap) {
	case 1: {
		glm::vec2 relation[N_ENEMIES1]{
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES1]{
			"images/enemies/Enemy1.png"
		};
		glm::ivec2 posInicial[N_ENEMIES1]{
			glm::ivec2(0, 50)
		};
		glm::ivec2 posFinal[N_ENEMIES1]{
			glm::ivec2(50, 50)
		};
		for (int i = 0; i < N_ENEMIES1; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}
	case 2: {
		glm::vec2 relation[N_ENEMIES2]{
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES2]{
			"images/enemies/Enemy1.png"
		};
		glm::ivec2 posInicial[N_ENEMIES2]{
			glm::ivec2(0, 50)
		};
		glm::ivec2 posFinal[N_ENEMIES2]{
			glm::ivec2(50, 50)
		};
		for (int i = 0; i < N_ENEMIES2; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}
	case 3: {
		glm::vec2 relation[N_ENEMIES3]{
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES3]{
			"images/enemies/Enemy1.png"
		};
		glm::ivec2 posInicial[N_ENEMIES3]{
			glm::ivec2(0, 50)
		};
		glm::ivec2 posFinal[N_ENEMIES3]{
			glm::ivec2(50, 50)
		};
		for (int i = 0; i < N_ENEMIES3; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}
	case 4: {
		glm::vec2 relation[N_ENEMIES4]{
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES4]{
			"images/enemies/Enemy1.png"
		};
		glm::ivec2 posInicial[N_ENEMIES4]{
			glm::ivec2(0, 50)
		};
		glm::ivec2 posFinal[N_ENEMIES4]{
			glm::ivec2(50, 50)
		};
		for (int i = 0; i < N_ENEMIES4; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}
	case 5: {
		glm::vec2 relation[N_ENEMIES5]{
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES5]{
			"images/enemies/Enemy1.png"
		};
		glm::ivec2 posInicial[N_ENEMIES5]{
			glm::ivec2(0, 50)
		};
		glm::ivec2 posFinal[N_ENEMIES5]{
			glm::ivec2(50, 50)
		};
		for (int i = 0; i < N_ENEMIES5; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}
	case 6: {
		glm::vec2 relation[N_ENEMIES6]{
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES6]{
			"images/enemies/Enemy1.png"
		};
		glm::ivec2 posInicial[N_ENEMIES6]{
			glm::ivec2(0, 50)
		};
		glm::ivec2 posFinal[N_ENEMIES6]{
			glm::ivec2(50, 50)
		};
		for (int i = 0; i < N_ENEMIES6; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}
	case 7: {
		glm::vec2 relation[N_ENEMIES7]{
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES7]{
			"images/enemies/Enemy1.png"
		};
		glm::ivec2 posInicial[N_ENEMIES7]{
			glm::ivec2(0, 50)
		};
		glm::ivec2 posFinal[N_ENEMIES7]{
			glm::ivec2(50, 50)
		};
		for (int i = 0; i < N_ENEMIES7; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}
	case 8: {
		glm::vec2 relation[N_ENEMIES8]{
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES8]{
			"images/enemies/Enemy1.png"
		};
		glm::ivec2 posInicial[N_ENEMIES8]{
			glm::ivec2(0, 50)
		};
		glm::ivec2 posFinal[N_ENEMIES8]{
			glm::ivec2(50, 50)
		};
		for (int i = 0; i < N_ENEMIES8; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}
	case 9: {
		glm::vec2 relation[N_ENEMIES9]{
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES9]{
			"images/enemies/Enemy1.png"
		};
		glm::ivec2 posInicial[N_ENEMIES9]{
			glm::ivec2(0, 50)
		};
		glm::ivec2 posFinal[N_ENEMIES9]{
			glm::ivec2(50, 50)
		};
		for (int i = 0; i < N_ENEMIES9; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
	}
	case 10: {
		glm::vec2 relation[N_ENEMIES10]{
			glm::vec2(1.f, 1.f / 4.f)
		};
		string nameImage[N_ENEMIES10]{
			"images/enemies/Enemy1.png"
		};
		glm::ivec2 posInicial[N_ENEMIES10]{
			glm::ivec2(0, 50)
		};
		glm::ivec2 posFinal[N_ENEMIES10]{
			glm::ivec2(50, 50)
		};
		for (int i = 0; i < N_ENEMIES10; i++) {
			Enemy* e = new Enemy;
			e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, relation[i], nameImage[i], posInicial[i], posFinal[i]);
			e->setPosition(posInicial[i]);
			e->setTileMap(map);
			enemy.push_back(e);
		}
		break;
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
}

// Els hi posem a tots els mapes "levelXY.txt"
// On X fa referencia a la dificultat i Y al nivell en si
void Level::nextMap () {
	if (actualMap + 1 != 6 && actualMap + 1 != 11) {
		int numberOfTheNewMap = int(addressActualMap[13]) + 1;
		addressActualMap[13] = char(numberOfTheNewMap);
		actualMap++;
	}
}

void Level::previousMap() {
	if (actualMap - 1 != 0 && actualMap - 1 != 5) {
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

void Level::collisionPlayerEnemy() {}

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