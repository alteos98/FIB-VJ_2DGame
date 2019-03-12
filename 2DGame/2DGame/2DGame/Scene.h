#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Player.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	virtual void init() = 0;
	virtual void update(int deltaTime) = 0;
	virtual void render() = 0;

protected:
	void initShaders();
	ShaderProgram texProgram;

};


#endif // _SCENE_INCLUDE

