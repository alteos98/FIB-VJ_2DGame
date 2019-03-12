#ifndef _BUTTON_INCLUDE
#define _BUTTON_INCLUDE


#include "Sprite.h"
#include "TileMap.h"

class Button
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getposB();
	int getWidth();
	int getHeight();
private:
	glm::ivec2 tileMapDispl, posButton;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};


#endif // _BUTTON_INCLUDE
