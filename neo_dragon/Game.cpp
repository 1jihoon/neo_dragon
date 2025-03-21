#include "Game.h"

//Game.h���� �� �����ڿ� �Ҹ��ڸ� ���⿡ ���� �ͼ� ó���Ѵ�.
Game::Game() {
	initVariable();
	initwindow();
	initBackground();
	loadTargetTextures();

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
	backgroundSprite = std::make_unique<sf::Sprite>(backgroundTexture);
}

int Game::loadTargetTextures() {
	if (!TargetTexture.loadFromFile("target.bmp")) return -1;

	energytargetSprite = std::make_unique<sf::Sprite>(TargetTexture);
	energytargetSprite->setOrigin(sf::Vector2f(TargetTexture.getSize().x / 2, TargetTexture.getSize().y / 2));
	energytargetSprite->setScale(sf::Vector2f(0.04f, 0.06f));
}

Game::~Game() {
	delete this -> window;
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
	if (clock_3.getElapsedTime().asSeconds() >= TargetTriggerTime) {
		isTargetvisible = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		sf::Vector2i pixelpos = sf::Mouse::getPosition(*window);
		sf::Vector2f worldpos = this->window->mapPixelToCoords(pixelpos);
		energytargetSprite->setPosition(worldpos);
		isTargetvisible = true;
		clock_3.restart();
	}
}

void Game::isTarget() {
	if (isTargetvisible) {
		this->window->draw(*energytargetSprite);
	}
}

void Game::render() {
	this->window->clear();
	this->window->draw(*backgroundSprite);
	this->window->draw(c.getSprite());
	isTarget();
	this->window->display();
	//����� ����� �巡�� �̹����� ���� ���⿡�� �̸� �׷��߸� �ڵ尡 ����Ǵµ�
	//�� �ൿ�� ���� �� �߱⿡ �翬�� �� ȭ���� ���� �� �ۿ� ����.
	//�� ������ ĳ���͸� ����ϴ� ���ο� �̹����� ǥ���ϱ� ���ؼ��� Game.h���� �����ϰ�
	//�Լ��� �����ؼ� �����ڸ� ���� �Լ��� ǥ���ϰ� ���������� render()���� ����
	//�̰� �����Լ� �������� �Ἥ �Ѳ����� ���� �ذ��ϰ� �����.
}