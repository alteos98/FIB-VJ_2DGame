#ifndef _BUTTON_INCLUDE
#define _BUTTON_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Button
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::ivec2 buttonSize, glm::vec2 relation, string nameImage);
	void update(int deltaTime);
	void render();
	void free();

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
	glm::ivec2 buttonSize;

};


#endif // _BUTTON_INCLUDE
