#include "Game.h"
#include <iostream>

//Game.h���� �� �����ڿ� �Ҹ��ڸ� ���⿡ ���� �ͼ� ó���Ѵ�.
Game::Game(): laser(sf::PrimitiveType::Lines, 2) {
	initVariable();
	initwindow();
	initBackground();
	loadTargetTextures();

	c.linkAnimation();
	c.loadTextures();
}
//loadTextures()�� �ִ� �ִϸ��̼� �Լ��� dragonSprite�� �ּҸ� �޾ƿͼ� ���⼭ 
//����� �Ǿ� �ϴµ� ���� �� �ּҸ� �ٸ� ������ ���ٸ� ��� �ִϸ��̼��� �� ���ٰ� �����Ѵ�
//�� �� �־ �ʱ�ȭ�ؾ� �ϴ� ���� ��������� �����ڿ� �־ �ʱ�ȭ�Ѵ�.

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

//���⼭���� run()�� ����� �Լ����� �� ���� �ʱ�ȭ�Ǵ°��� �ƴ� ��� ����Ǿ� �ϱ⿡
//�����ڿ� �־ �ʱ�ȭ�ϸ� �ȵȴ�. �� ���𰡸� ��� �߻����Ѿ� �ϴ� �ڵ���
//�����ڿ��� �ʱ�ȭ��Ű�� �ȵȴ�.
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

	laserOrigin = c.getEnergyBallPosition();

	if (clock_3.getElapsedTime().asSeconds() >= TargetTriggerTime) {
		isTargetvisible = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		sf::Vector2i pixelpos = sf::Mouse::getPosition(*window);
		sf::Vector2f worldpos = this->window->mapPixelToCoords(pixelpos);
		energytargetSprite->setPosition(worldpos);

		DragonState state = c.getCurrentState();
		//std::cout << "[State] ���� ����: " << static_cast<int>(c.getCurrentState()) << std::endl;
		if (worldpos.x > 400.f && state != DragonState::Rightkamehameha) {
			c.setCurrentState(DragonState::Rightkamehameha);
		}
		else if (worldpos.x <= 400.f && state != DragonState::LeftKamehameha) {
			c.setCurrentState(DragonState::LeftKamehameha);
		}

		laser[0].position = laserOrigin;
		laser[0].color = sf::Color::Red;
		  
		laser[1].position = worldpos;
		laser[1].color = sf::Color::Red;
		
		isTargetvisible = true;
		clock_3.restart();
	}
}

void Game::isTarget() {
	if (isTargetvisible) {
		this->window->draw(*energytargetSprite);
		this->window->draw(laser);
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