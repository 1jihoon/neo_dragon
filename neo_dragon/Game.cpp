#include "Game.h"

//Game.h에서 쓴 생성자와 소멸자를 여기에 갖고 와서 처리한다.
Game::Game() {
	initVariable();
	initwindow();
	initBackground();

	c.linkAnimation();
	c.loadTextures();
}
//loadTextures()에 있는 애니메이션 함수의 dragonSprite의 주소를 받아와서 여기서 
//사용이 되야 하는데 만약 그 주소를 다른 곳에다 쓴다면 적어도 애니메이션은 못 쓴다고 봐야한다

//praivate function
void Game::initVariable() {
	this->window = nullptr;
}

void Game::initwindow() {
	this -> window = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(800, 600)), "SFML Window");
}

int Game::initBackground() {
	if (!backgroundTexture.loadFromFile("satunus.bmp")) return -1;
	// 배경 스프라이트 설정
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
	// 이벤트 처리
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
	//배경을 비롯한 드래곤 이미지를 전부 여기에서 미리 그려야만 코드가 실행되는데
	//그 행동을 먼저 안 했기에 당연히 흰 화면이 나올 수 밖에 없다.
	//즉 앞으로 캐릭터를 담당하는 새로운 이미지를 표현하기 위해서는 Game.h에다 정의하고
	//함수를 정의해서 생성자를 만들어서 함수로 표현하고 최종적으로 render()에다 쓰고
	//이걸 메인함수 마지막에 써서 한꺼번에 전부 해결하게 만든다.
}



