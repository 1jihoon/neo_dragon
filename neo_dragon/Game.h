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
	sf::Sprite *sprite;
	sf::VideoMode videomode;
	void initVariable();
	void initwindow();
	sf::Sprite *backgroundSprite;
	sf::Texture backgroundTexture;
	int initBackground();
	Character c;
};
