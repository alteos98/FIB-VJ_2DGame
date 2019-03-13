#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Menu.h"
#include "Level.h"


#define SCREEN_WIDTH 1080 //640 //720
#define SCREEN_HEIGHT 810 //480 //540


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button, int x, int y);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	enum MenuTypes {
		MAINMENU, PLAYING, SELECTDIFFICULTY, INSTRUCTIONS, CREDITS, PAUSE, ENDSCREEN
	};

	bool bPlay;                       // Continue to play game?
	Level level;                      // Scene to render
	Menu menu;
	bool keys[256], specialKeys[256]; // Store key states so that we can have access at any time
	MenuTypes actualMenu;
	bool isPlaying;	// True -> the user is in a level, False -> the user is in a menu
	bool bLeft;	// True -> left button of the mouse is pressed
	int mouseX, mouseY;
	int difficulty;

public:
	void updateMenu(MenuTypes menuType);
};


#endif // _GAME_INCLUDE


