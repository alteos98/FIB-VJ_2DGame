#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"

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

	void update(int deltaTime);
	void render();

	void nextMap();
	void previousMap();
	void changingMapConditions();
	void collisionPlayerEnemy();

private:
	string addressActualMap;
	int actualMap; // 1 ~ 5 easy, 6 ~ 10 hard
	bool isOnFloor; // True -> Player is on the floor, False -> Player is on the roof

	TileMap *map;
	Player *player;
	glm::ivec2 posPlayer;
	vector<Enemy*> enemy;
	float currentTime;
	glm::mat4 projection;

	void initShaders();
	ShaderProgram texProgram;
};