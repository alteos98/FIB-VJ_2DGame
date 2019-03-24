#ifndef _STALACTITE_INCLUDE
#define _STALACTITE_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Stalactite
{

public:
	Stalactite();
	~Stalactite();
	void init(const glm::ivec2 &stalactitePos, ShaderProgram &shaderProgram, glm::ivec2 stalactiteSize);
	void update(int deltaTime);
	void render();
	void changeAnimation(int i);

	bool hasToFall(glm::ivec2 & playerPos);
	bool outOfMap();

	void setTileMap(TileMap *tileMap);
	glm::ivec2 getPosition();
	void setPosition(const glm::vec2 &pos);
	void setMargin(int marginX, int marginY);
	void setLeftX(int leftX);
	void setRightX(int rightX);
	void setDownY(int downY);
	void setFallingVelocity(int fallingVelocity);
	void setFalling(bool b);

	int getWidth();
	int getHeight();
	int getLeftX();
	int getRightX();
	int getDownY();
	int getFallingVelocity();
	bool getFalling();

private:
	// representen els marges respecte la posició de l'objecte que
	// si es superen faràn caure l'estalactita
	// marge per dalt no té sentit
	int leftX, rightX, downY;
	bool falling;
	int fallingVelocity;

	glm::ivec2 stalactitePos, stalactiteSize;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};


#endif // _STALACTITE_INCLUDE
