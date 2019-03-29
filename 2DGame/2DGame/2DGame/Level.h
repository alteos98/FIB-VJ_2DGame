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
#include "Treasure.h"

class Level
{
public:
	Level();
	~Level();
	void init(int difficulty);
	void update(int deltaTime);
	void render();

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
	void loadTresure();
	void loadPauseButton();

	void setMap(int newMap);
	void nextMap();
	void previousMap();
	void changingMapConditions();

	bool collisionPlayerEnemies();
	bool collisionPlayerPlataforma(int& PlataformaAc);
	bool collisionPlayerPlataformaLateral(int& PlataformaAc);
	bool collisionPlayerGuardar(int & GuardadoActual);
	bool collisionPlayerSpikes();
	bool collisionPlayerStar();
	bool collisionPlayerLightning();
	bool collisionPlayerStalactite();
	bool collisionPlayerTreasure();

	int getActualMap();
	int getDifficulty();

	void setPlayerPosition(glm::ivec2 newPlayerPos);

	bool buttonPress(int x, int y);

private:
	string addressActualMap;
	int actualMap; // 11 ~ 15 easy, 21 ~ 27 hard
	bool isOnFloor; // True -> Player is on the floor, False -> Player is on the roof
	int difficulty;


	// INTERACTUABLE

	TileMap *map;
	Player *player;
	Button* pauseButton;
	vector<Enemy*> enemy;
	vector<Plataforma*> plataforma;
	vector<Guardar*> guardar;
	vector<Spike*> spikes;
	vector<Lightning*> lightning;
	vector<Stalactite*> stalactites;
	Star* star;
	Treasure* treasure;


	// OTHERS

	glm::ivec2 posPlayer, posPlayerIni, sizePlayer;
	float currentTime, currentTimeCollision;
	vector<glm::ivec3> posicionesGuardar;
	glm::mat4 projection;
	int numGuardado;
	bool mapacambiado;
	bool ContactoPlat;
	bool collisioned;
	ShaderProgram texProgram;


	// FUNCTIONS

	void InitMusica();
	void InitSoundEffects();
	bool collision(glm::ivec2 &pos1, glm::ivec2 &size1, glm::ivec2 &pos2, glm::ivec2 &size2);
	bool collisionLateral(glm::ivec2 &pos1, glm::ivec2 &size1, glm::ivec2 &pos2, glm::ivec2 &size2);
	void changeMap();
	void Actualizarllama();
	void InitPosGuardar();
	void initShaders();


	// DEFINITIONS

	int enemiesVelocityEasy[5]{
		NULL, NULL, 6, 6, 6
	};
	int enemiesVelocityHard[7]{
		8, 6, 8, 8, 10, 10, 10
	};
	int plataformaVelocityHard[7]{
		2,	2,	2,	2,	2,	2,	2
	};

};