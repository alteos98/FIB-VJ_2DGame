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
	loadMap();
}

void Level::loadMap() {
	initShaders();
	map = TileMap::createTileMap(addressActualMap, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
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

	// Afegir condicions de que si el player se surt de la pantalla canvii de nivell
	posPlayer = player->getPosition();
	printf("%i , %i \n", posPlayer.x, posPlayer.y);
	if (posPlayer.x >= (SCREEN_WIDTH - 35)) { // posPlayer.x arriba com a molt a 608; 640 - 608 = 32
		posPlayer.x = 5;
		nextMap();
		newPositionPlayer();
		loadMap();
	}
	if (posPlayer.x <= (0)) { // posPlayer.x arriba com a molt a 608; 640 - 608 = 32
		posPlayer.x = 600;
		previousMap();
		newPositionPlayer();
		loadMap();
	}
	if (posPlayer.y >= (SCREEN_HEIGHT - 35)) { // posPlayer.x arriba com a molt a 608; 640 - 608 = 32
		posPlayer.y = 5;
		nextMap();
		newPositionPlayer();
		loadMap();
	}
	if (posPlayer.y <= (0)) { // posPlayer.x arriba com a molt a 608; 640 - 608 = 32
		posPlayer.y = 440;
		previousMap();
		newPositionPlayer();
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

// Funció per establir la nova posició del player en funció del nou mapa
void Level::newPositionPlayer () {}

// Els hi posem a tots els mapes "levelXY.txt"
// On X fa referencia a la dificultat i Y al nivell en si
void Level::nextMap () {
	if (actualMap + 1 != 5 && actualMap + 1 != 10) {
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