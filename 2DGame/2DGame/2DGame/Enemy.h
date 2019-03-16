#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Enemy is basically a Sprite that represents the Enemy. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Enemy
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::vec2 relation, string nameImage, glm::ivec2 posInicial, glm::ivec2 posFinal, int velocity);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition();
	void setAnimation(int i);

private:
	glm::ivec2 tileMapDispl, posEnemy, posInicial, posFinal;
	float incrementX, incrementY; // increment for each update to the position of the enemy
	int nMovement, nTotalMovements; // número de moviments que farà
	bool goingReturning; // True -> going to posFinal, False -> returning to posInicial
	int velocity;

	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	glm::ivec2 quadSize;

	void newPosition();

};


#endif // _ENEMY_INCLUDE


