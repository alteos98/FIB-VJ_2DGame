#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Plataforma.h"
#include "Button.h"
#include "Guardar.h"
#include "Spike.h"
#include "Star.h"

class Level
{
public:
	Level();
	~Level();
	void init(int difficulty);

	void load();
	void loadMap();
	void loadSpikes();
	void loadPlayer();
	void loadEnemies();
	void loadPlataforma();
	void loadGuardar();
	void loadStar();

	void update(int deltaTime);
	void render();

	void nextMap();
	void previousMap();
	void changingMapConditions();
	bool buttonPress(int x, int y);
	bool collisionPlayerEnemies();

	bool collisionPlayerPlataforma(int& PlataformaAc);
	bool collisionPlayerPlataformaDown();

	bool collisionPlayerGuardar(int & GuardadoActual);
	bool collisionPlayerSpikes();
	bool collisionPlayerStar();

	int getActualMap();

private:
	string addressActualMap;
	int actualMap; // 11 ~ 15 easy, 21 ~ 25 hard
	bool isOnFloor; // True -> Player is on the floor, False -> Player is on the roof
	int difficulty;

	void changeMap();
	void Actualizarllama();
	bool mapacambiado;
	bool ContactoPlat;
	TileMap *map;
	Player *player;
	glm::ivec2 posPlayer;
	vector<Enemy*> enemy;
	vector<Plataforma*> plataforma;
	vector<Guardar*> guardar;
	vector<Spike*> spikes;
	Star* star;
	int numGuardado;
	float currentTime;
	glm::mat4 projection;
	Button* pauseButton;
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
	int plataformaVelocityHard[5]{
		2,	2,	2,	2,	2
	};

};