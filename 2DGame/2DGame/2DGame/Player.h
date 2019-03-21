#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, bool isOnFloor);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition();
	bool getIsOnFloor();
	bool getbGravity();
	Sprite* getSprite();
	void setAnimation(int i);
	void setIsOnFloor(bool floor);
	int getWidth();
	int getHeight();
	void setGravity(bool b);

private:
	bool bJumping;
	bool bGravity; // true if the player is inverting / reverting the gravity
	bool isOnFloor;

	glm::ivec2 tileMapDispl, posPlayer, playerSize;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};


#endif // _PLAYER_INCLUDE


