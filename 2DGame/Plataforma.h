#ifndef _PLATAFORMA_INCLUDE
#define _PLATAFORMA_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Enemy is basically a Sprite that represents the Enemy. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Plataforma
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::vec2 relation, string nameImage, glm::ivec2 posInicial, glm::ivec2 posFinal, int velocity);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition();
	void setAnimation(int i);
	int getWidth();
	int getHeight();
	glm::ivec2 getIncrease();

private:
	glm::ivec2 tileMapDispl, posPlat, posInicial, posFinal, platSize;
	float incrementX, incrementY; // increment for each update to the position of the enemy
	int nMovement, nTotalMovements; // n�mero de moviments que far�
	bool goingReturning; // True -> going to posFinal, False -> returning to posInicial
	int velocity;

	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

	void newPosition();

};


#endif // _PLATAFORMA_INCLUDE
