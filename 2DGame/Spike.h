#ifndef _SPIKE_INCLUDE
#define _SPIKE_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Spike
{

public:
	Spike();
	~Spike();
	void init(const glm::ivec2 &posSpike, ShaderProgram &shaderProgram, glm::ivec2 spikeSize, bool upOrDown);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition();
	int getWidth();
	int getHeight();

private:
	glm::ivec2 posSpike, spikeSize;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	int id;
};


#endif // _SPIKE_INCLUDE
