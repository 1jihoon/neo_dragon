#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Animation.h"
#include "Sound.h"


class Game {

public:
	//생성자, 소멸자
	Game();
	virtual ~Game();
	//지금은 괜찮지만 만일 Game 클래스가 상속관계에 놓여지게 된다면 virtual을 쓰지 않을 경우
	//부모 소멸자만 호출되고 자식 소멸자는 호출되지 않는 상황에 놓이게 되므로 virtual을 써야 한다.

	void run();
	void pollEvents();
	void render();
	void update();
	void handleInput();

private:
	sf::RenderWindow* window;
	sf::Sprite *sprite;
	sf::VideoMode videomode;
	void initVariable();
	void initwindow();
	sf::Sprite *backgroundSprite;
	sf::Texture backgroundTexture;
	int initBackground();
	Character c;
};
