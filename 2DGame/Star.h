#ifndef _STAR_INCLUDE
#define _STAR_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Star
{

public:
	Star();
	~Star();
	void init(const glm::ivec2 &posStar, ShaderProgram &shaderProgram, glm::ivec2 starSize);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition();
	int getWidth();
	int getHeight();

private:
	glm::ivec2 posStar, starSize;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	int id;
};


#endif // _STAR_INCLUDE
