#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Enemy is basically a Sprite that represents the Enemy. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Enemy
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::vec2 relation, string nameImage);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition();
	void setAnimation(int i);

private:
	glm::ivec2 tileMapDispl, posEnemy;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	glm::ivec2 quadSize;

};


#endif // _ENEMY_INCLUDE


