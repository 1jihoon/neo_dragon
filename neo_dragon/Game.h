#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Animation.h"
#include "Sound.h"


class Game {

public:
	//������, �Ҹ���
	Game();
	virtual ~Game();
	//������ �������� ���� Game Ŭ������ ��Ӱ��迡 �������� �ȴٸ� virtual�� ���� ���� ���
	//�θ� �Ҹ��ڸ� ȣ��ǰ� �ڽ� �Ҹ��ڴ� ȣ����� �ʴ� ��Ȳ�� ���̰� �ǹǷ� virtual�� ��� �Ѵ�.

	void run();
	void pollEvents();
	void render();
	void update();
	void handleInput();

private:
	sf::RenderWindow* window;
	//unique_ptr�� ���Ǹ� �� �߱⿡ delete�� �ؾߵ�
	std::unique_ptr<sf::Sprite> backgroundSprite;
	std::unique_ptr<sf::Sprite> energytargetSprite;
	std::unique_ptr<sf::Sprite> laserSprite;
	//unique_ptr�� ������ ����� �޸� ���� �� �ص� ��

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
