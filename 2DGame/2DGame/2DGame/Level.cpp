#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Level.h"
#include "Game.h"

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 10
#define INIT_PLAYER_Y_TILES 20

Level::Level()
{
	map = NULL;
	player = NULL;
}


Level::~Level()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
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
	loadMap();
}

void Level::loadMap() {
	initShaders();
	map = TileMap::createTileMap(addressActualMap, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, isOnFloor);
	player->setPosition(posPlayer);
	posPlayer = player->getPosition();
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Level::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);

	isOnFloor = player->getIsOnFloor();
	cout << isOnFloor << endl;

	// Afegir condicions de que si el player se surt de la pantalla canvii de nivell
	posPlayer = player->getPosition();
	if (posPlayer.x >= SCREEN_WIDTH) {
		posPlayer.x = 0;
		nextMap();
		loadMap();
	}
	if (posPlayer.x < -25) {
		posPlayer.x = 620;
		previousMap();
		loadMap();
	}
	if (posPlayer.y >= SCREEN_HEIGHT) {
		posPlayer.y = 5;
		nextMap();
		loadMap();
	}
	if (posPlayer.y < -25) {
		posPlayer.y = 440;
		previousMap();
		loadMap();
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