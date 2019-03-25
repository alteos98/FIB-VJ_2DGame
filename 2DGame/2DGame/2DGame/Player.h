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


	void setAnimation(int i);
	void setIsOnFloor(bool floor);
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setSize(glm::ivec2 newSize);


private:
	bool bJumping;
	bool bGravity; // true if the player is inverting / reverting the gravity
	bool isOnFloor;
	int fallStep;

	bool needdesplas;
	bool hasdesplas;
	float desplas;
	float sentidodesplas;
	int time;



	glm::ivec2 tileMapDispl, posPlayer, playerSize;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	ShaderProgram shaderProgram;
};


#endif // _PLAYER_INCLUDE


