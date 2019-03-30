#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include <time.h>
#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::ivec2 size, bool isOnFloor);
	void initSprite();
	void update(int deltaTime);
	void render();
	
	glm::ivec2 getPosition();
	bool getIsOnFloor();
	bool getbGravity();
	Sprite* getSprite();
	int getWidth();
	int getHeight();
	void setGravity(bool b);
	int getFallStep();
	bool getBGravity();
	bool isLittle();
	TileMap* getTileMap();

	void setAnimation(int i);
	void setIsOnFloor(bool floor);
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setSize(glm::ivec2 newSize);
	void setLittle(bool little);
	void setHasdesplas(bool b);

private:
	bool cambiosentido = true;
	bool bJumping;
	bool bGravity; // true if the player is inverting / reverting the gravity
	bool isOnFloor;
	bool little = false;
	int fallStep;
	int pasos = 0;

	bool needdesplas;
	bool needdesplasder;
	bool needdesplasizq;
	bool hasdesplas = false;
	float desplas;
	float sentidodesplas;
	float time;
	int aceleracion();
	float ac;

	glm::ivec2 tileMapDispl, posPlayer, playerSize;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	ShaderProgram shaderProgram;
};


#endif // _PLAYER_INCLUDE


