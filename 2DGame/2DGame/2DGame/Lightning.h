#ifndef _LIGHTNING_INCLUDE
#define _LIGHTNING_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Lightning
{

public:
	Lightning();
	~Lightning();
	void init(const glm::ivec2 &posLightning, ShaderProgram &shaderProgram, glm::ivec2 lightningSize, bool orientation);
	void update(int deltaTime);
	void render();

	void changeAnimation(int i);
	
	void setTileMap(TileMap *tileMap);
	glm::ivec2 getPosition();
	void setPosition(const glm::vec2 &pos);
	int getWidth();
	int getHeight();
	bool getOrientation();
	void setOrientation(bool orientation);

private:
	glm::ivec2 posLightning, lightningSize;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	bool orientation; // True -> vertical; False -> horizontal
};


#endif // _LIGHTNING_INCLUDE
