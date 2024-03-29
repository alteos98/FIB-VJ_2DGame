#ifndef _GUARDAR_INCLUDE
#define _GUARDAR_INCLUDE


#include "Sprite.h"
#include "TileMap.h"

class Guardar
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, glm::ivec2 buttonSize, int id);
	void update(int deltaTime);
	void render();
	int getID();
	void Cambiar_llama(bool llama);
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getposG();
	int getWidth();
	int getHeight();

private:
	glm::ivec2 tileMapDispl, posGuardar;
	Texture spritesheet;
	Sprite *sprite, *spriteBase;
	TileMap *map;
	glm::ivec2 GuardarSize;
	int id;
};


#endif // _GUARDAR_INCLUDE
