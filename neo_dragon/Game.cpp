#include "Game.h"

//Game.h���� �� �����ڿ� �Ҹ��ڸ� ���⿡ ���� �ͼ� ó���Ѵ�.
Game::Game() {
	initVariable();
	initwindow();
	initBackground();

	c.linkAnimation();
	c.loadTextures();
}
//loadTextures()�� �ִ� �ִϸ��̼� �Լ��� dragonSprite�� �ּҸ� �޾ƿͼ� ���⼭ 
//����� �Ǿ� �ϴµ� ���� �� �ּҸ� �ٸ� ������ ���ٸ� ��� �ִϸ��̼��� �� ���ٰ� �����Ѵ�

//praivate function
void Game::initVariable() {
	this->window = nullptr;
}

void Game::initwindow() {
	this -> window = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(800, 600)), "SFML Window");
}

int Game::initBackground() {
	if (!backgroundTexture.loadFromFile("satunus.bmp")) return -1;
	// ��� ��������Ʈ ����
	backgroundSprite = new sf::Sprite(backgroundTexture);
}

Game::~Game() {
	delete this->window;
}

void Game::run() {
	while (window && window->isOpen()) {
		pollEvents();
		handleInput();
		update();
		render();
	}
}

void Game::pollEvents()
{
	// �̺�Ʈ ó��
	while (const std::optional<sf::Event> event = window->pollEvent()) {
		if (event->is<sf::Event::Closed>()) window->close();
	}
}

void Game::handleInput() {
	c.handleInput();
}

void Game::update() {
	c.update();
}

void Game::render() {
	this->window->clear();
	this->window->draw(*backgroundSprite);
	this->window->draw(c.getSprite());
	this->window->display();
	//����� ����� �巡�� �̹����� ���� ���⿡�� �̸� �׷��߸� �ڵ尡 ����Ǵµ�
	//�� �ൿ�� ���� �� �߱⿡ �翬�� �� ȭ���� ���� �� �ۿ� ����.
	//�� ������ ĳ���͸� ����ϴ� ���ο� �̹����� ǥ���ϱ� ���ؼ��� Game.h���� �����ϰ�
	//�Լ��� �����ؼ� �����ڸ� ���� �Լ��� ǥ���ϰ� ���������� render()���� ����
	//�̰� �����Լ� �������� �Ἥ �Ѳ����� ���� �ذ��ϰ� �����.
}



