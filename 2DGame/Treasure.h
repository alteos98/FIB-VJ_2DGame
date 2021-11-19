#ifndef _TREASURE_INCLUDE
#define _TREASURE_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Treasure
{

public:
	Treasure();
	~Treasure();
	void init(const glm::ivec2 &treasurePos, ShaderProgram &shaderProgram, glm::ivec2 treasureSize);
	void update(int deltaTime);
	void render();
	void changeAnimation(int i);

	void open();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

	glm::ivec2 getPosition();
	int getWidth();
	int getHeight();

private:
	glm::ivec2 treasurePos, treasureSize;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};


#endif // _TREASURE_INCLUDE
