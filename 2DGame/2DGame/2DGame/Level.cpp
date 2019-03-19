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

#define GUARDAR11 1
#define GUARDAR12 1
#define GUARDAR13 1
#define GUARDAR14 1
#define GUARDAR15 1

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
	for (unsigned int i = 0; i < guardar.size(); ++i) {
		guardar[i] = NULL;
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
}


void Level::InitPosGuardar() {
	vector<glm::ivec3> g(3);
	g[0] = glm::ivec3(780, 482,1); // El tercer elemento es el mapa en el que es la posicion
	g[1] = glm::ivec3(850, 482, 2);
	g[2] = glm::ivec3(64, 482, 3);
	posicionesGuardar = g;
}

void Level::init(int difficulty)
{
	InitPosGuardar();
	if (difficulty == 1) {
		addressActualMap = "levels/level11.txt";
		actualMap = 11;
		posPlayer = glm::vec2(300, 200);
	}
		
	else if (difficulty == 2) {
		addressActualMap = "levels/level22.txt";
		actualMap = 22;
		posPlayer = glm::vec2(50, 50);
	}

	initShaders();
	player = new Player();
	isOnFloor = true;
	this->difficulty = difficulty;
	numGuardado = -1;
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
	guardar.clear();
	loadEnemies();
	loadGuardar();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Level::loadMap() {
	mapacambiado = true;
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
		/*case 21: {
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
		}*/
		}
	}
}

void Level::loadGuardar() {
	if (difficulty == 1) { // easy
		switch (actualMap) {
		case 11: {
			glm::ivec2 posIni[GUARDAR11]{
				glm::ivec2(posicionesGuardar[0].x, posicionesGuardar[0].y)

			};
			int id = 1;
			for (int i = 0; i < GUARDAR11; i++) {
				Guardar* g = new Guardar;
				g->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(64,64), id);
				g->setPosition(posIni[i]);
				g->setTileMap(map);
				guardar.push_back(g);
			}
			break;
		}
		case 12: {// Deberia hacer un vector diciendo que guardados va en cada nivel para que solo cargue esos o algo asi 
			glm::ivec2 posIni[GUARDAR12]{
				glm::ivec2(posicionesGuardar[1].x, posicionesGuardar[1].y)
			};
			int id = 2;
			for (int i = 0; i < GUARDAR12; i++) {
				Guardar* g = new Guardar;
				g->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(64, 64), id);
				g->setPosition(posIni[i]);
				g->setTileMap(map);
				guardar.push_back(g);
			}
			break;
		}
		case 13: {// Deberia hacer un vector diciendo que guardados va en cada nivel para que solo cargue esos o algo asi 
			glm::ivec2 posIni[GUARDAR13]{
				glm::ivec2(posicionesGuardar[2].x, posicionesGuardar[2].y)
			};
			int id = 3;
			for (int i = 0; i < GUARDAR13; i++) {
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
}

void Level::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);

	for (unsigned int i = 0; i < enemy.size(); ++i)
		enemy[i]->update(deltaTime);
	for (unsigned int i = 0; i < guardar.size(); ++i)
		guardar[i]->update(deltaTime);

	changingMapConditions();
	
	if (collisionPlayerEnemies()) {
		cout << "collision" << endl;
		if (numGuardado != -1) posPlayer = glm::ivec2(posicionesGuardar[numGuardado-1].x, posicionesGuardar[numGuardado-1].y);
		// fer que el player reapareixi a l'ultim punt de guardat
		player->setPosition(glm::vec2(posPlayer.x, posPlayer.y));
		changeMap();
		player->setIsOnFloor(true);

	}
	int aux = -1;
	if (collisionPlayerGuardar(aux)) {
		cout << "colision llama" << aux << numGuardado << endl;
		if (aux != -1 && numGuardado != aux) {
			//if (numGuardado != -1) guardar[numGuardado-1]->Cambiar_llama();
			numGuardado = aux;
			//guardar[numGuardado-1]->Cambiar_llama();
			Actualizarllama();
		}
	}
	if (mapacambiado) { Actualizarllama(); mapacambiado = false; }
}

void Level::changeMap()
{
	//cout << char(posicionesGuardar[numGuardado - 1].z) + '0';
	addressActualMap[13] = char(posicionesGuardar[numGuardado - 1].z) + '0';
	actualMap = (addressActualMap[12] - '0')*10 + posicionesGuardar[numGuardado - 1].z;
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
	for (unsigned int i = 0; i < guardar.size(); ++i) {
		guardar[i]->render();
	}
	b->render();
}

// Els hi posem a tots els mapes "levelXY.txt"
// On X fa referencia a la dificultat i Y al nivell en si
void Level::nextMap () {
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
	cout << posPlayer.x << endl;

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
			nextMap();
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
			nextMap();
			load();
		}
		else if (posPlayer.x > SCREEN_WIDTH) {
			posPlayer.x = -32;
			previousMap();
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
			nextMap();
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
			previousMap();
			load();
		}
	}
	else if (actualMap == 24) {
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
	else if (actualMap == 25) {
		if (posPlayer.y < -128) {
			posPlayer.y = SCREEN_HEIGHT;
			if (isOnFloor)
				isOnFloor = !isOnFloor;
			nextMap();
			load();
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
	else if (actualMap == 26) {
		if (posPlayer.y >= SCREEN_HEIGHT + 20) {
			posPlayer.y = 0;
			if (!isOnFloor)
				isOnFloor = !isOnFloor;
			previousMap();
			load();
		}
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

bool Level::collisionPlayerGuardar(int & GuardadoActual) {
	bool b = false;
	posPlayer = player->getPosition();

	for (unsigned int i = 0; i < guardar.size() && !b; ++i) {
		if (collision(posPlayer, glm::ivec2(64, 64), guardar[i]->getposG(), glm::ivec2(64, 128))) {
			b = true;
			GuardadoActual = guardar[i]->getID();
			cout << guardar[i]->getID();
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