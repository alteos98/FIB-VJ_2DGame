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
#include "Lightning.h"
#include "Stalactite.h"
#include "AudioEngine.h"

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
	void loadLightning();
	void loadStalactites();
	void LoadMusicAndSoundEffects();

	void update(int deltaTime);
	void render();

	void setMap(int newMap);
	void nextMap();
	void previousMap();
	void changingMapConditions();
	bool buttonPress(int x, int y);

	bool collisionPlayerEnemies();
	bool collisionPlayerPlataforma(int& PlataformaAc);
	bool collisionPlayerGuardar(int & GuardadoActual);
	bool collisionPlayerSpikes();
	bool collisionPlayerStar();
	bool collisionPlayerLightning();
	bool collisionPlayerStalactite();

	int getActualMap();
	int getDifficulty();

	void setPlayerPosition(glm::ivec2 newPlayerPos);

private:
	string addressActualMap;
	int actualMap; // 11 ~ 15 easy, 21 ~ 26 hard
	bool isOnFloor; // True -> Player is on the floor, False -> Player is on the roof
	int difficulty;

	void changeMap();
	void Actualizarllama();
	bool mapacambiado;
	bool ContactoPlat;
	TileMap *map;
	Player *player;
	glm::ivec2 posPlayer, posPlayerIni;
	vector<Enemy*> enemy;
	vector<Plataforma*> plataforma;
	vector<Guardar*> guardar;
	vector<Spike*> spikes;
	vector<Lightning*> lightning;
	vector<Stalactite*> stalactites;
	Star* star;
	int numGuardado;
	float currentTime, currentTimeCollision;
	glm::mat4 projection;
	Button* pauseButton;
	vector<glm::ivec3> posicionesGuardar;
	void InitPosGuardar();
	void InitMusica();
	void InitSoundEffects();
	bool collisioned;

	bool collision(glm::ivec2 &pos1, glm::ivec2 &size1, glm::ivec2 &pos2, glm::ivec2 &size2);

	void initShaders();
	ShaderProgram texProgram;

	int enemiesVelocityEasy[5]{
		NULL, NULL, 4, 4, 4
	};
	int enemiesVelocityHard[6]{
		8, 8, 8, 8, 10, 8
	};
	int plataformaVelocityHard[5]{
		2,	2,	2,	2,	2
	};

};