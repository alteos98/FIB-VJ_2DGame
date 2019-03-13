#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"

class Level
{
public:
	Level();
	~Level();
	void init(int difficulty);
	void loadMap();
	void update(int deltaTime);
	void render();
	void nextMap();
	void newPositionPlayer();

private:
	string addressActualMap;
	int actualMap; // 1 ~ 5 easy, 6 ~ 10 hard
	TileMap *map;
	Player *player;
	glm::ivec2 posPlayer;
	float currentTime;
	glm::mat4 projection;

	void initShaders();
	ShaderProgram texProgram;
};