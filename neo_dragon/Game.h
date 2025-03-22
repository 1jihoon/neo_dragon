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
	//unique_ptr로 정의를 안 했기에 delete를 해야됨
	std::unique_ptr<sf::Sprite> backgroundSprite;
	std::unique_ptr<sf::Sprite> energytargetSprite;
	std::unique_ptr<sf::Sprite> laserSprite;
	//unique_ptr로 변수를 만들면 메모리 해제 안 해도 됨

	sf::Vector2f direction;
	sf::Vector2f laserOrigin;
	float length;
	float angle;
	float baseWidth;
	sf::VertexArray laser;

	sf::Texture TargetTexture;
	sf::VideoMode videomode;
	void initVariable();
	void initwindow();
	sf::Texture backgroundTexture;
	int initBackground();
	int loadTargetTextures();
	void isTarget();
	Character c;
	Animation a;
	sf::Clock clock_3;
	bool isTargetvisible = false;
	bool isTargetTrue = false;
	float TargetTriggerTime = 3.0f;
};
