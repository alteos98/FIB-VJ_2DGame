#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Button.h"
#include "Guardar.h"

class Level
{
public:
	Level();
	~Level();
	void init(int difficulty);

	void load();
	void loadMap();
	void loadPlayer();
	void loadEnemies();
	void loadGuardar();

	void update(int deltaTime);
	void render();

	void nextMap();
	void previousMap();
	void changingMapConditions();
	bool buttonPress(int x, int y);
	bool collisionPlayerEnemies();
	bool Level::collisionPlayerGuardar(int & GuardadoActual);

private:
	string addressActualMap;
	int actualMap; // 11 ~ 15 easy, 21 ~ 25 hard
	bool isOnFloor; // True -> Player is on the floor, False -> Player is on the roof
	int difficulty;

	void changeMap();
	void Actualizarllama();
	bool mapacambiado;
	TileMap *map;
	Player *player;
	glm::ivec2 posPlayer;
	vector<Enemy*> enemy;
	vector<Guardar*> guardar;
	int numGuardado;
	float currentTime;
	glm::mat4 projection;
	Button* b;
	vector<glm::ivec3> posicionesGuardar;
	void InitPosGuardar();

	bool collision(glm::ivec2 &pos1, glm::ivec2 &size1, glm::ivec2 &pos2, glm::ivec2 &size2);

	void initShaders();
	ShaderProgram texProgram;

	int enemiesVelocityEasy[5]{
		NULL, NULL, 4, 4, 4
	};
	int enemiesVelocityHard[5]{
		2, 2, 2, 2, 2
	};

};