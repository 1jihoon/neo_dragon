#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>

class Animation {
private:
	// 날개 애니메이션 변수
	int rightwingFrame = 0;
	int leftwingFrame = 0;
	std::vector<sf::Texture> rightwingFrames;
	std::vector<sf::Texture> leftwingFrames;
	sf::Clock RightwingClock;
	sf::Clock LeftwingClock;
	sf::Sprite* targetSprite = nullptr;
	float animationSpeed = 0.5f;
	float frameDuration = 0.05f;

	// 스파크 애니메이션 변수
	int sparkFrame = 0;
	std::vector<sf::Texture> sparkFrames;
	sf::Clock sparkClock;
	float sparkSpeed = 2.5f;
	float sparkDuration = 0.05f;


	//오른쪽으로 걷기 애니메이션 변수
	int rightWalkFrame = 0;
	std::vector<sf::Texture> rightWalkFrames;
	sf::Clock rightWalkClock;
	float rightWalkSpeed = 1.0f;
	float rightWalkDuration = 0.2f;

	//왼쪽으로 걷기 애니메이션 변수
	int leftWalkFrame = 0;
	std::vector<sf::Texture> leftWalkFrames;
	sf::Clock leftWalkClock;
	float leftWalkSpeed = 1.0f;
	float leftWalkDuration = 0.2f;

	//초사이어인 아우라 애니메이션 변수
	int supersaiyanFrame = 0;
	std::vector<sf::Texture> supersaiyanFrames;
	sf::Clock superClock;
	float superSpeed = 1.0f;
	float superDuration = 0.2f;

public:
	Animation();
	virtual ~Animation();

	void setTargetSprite(sf::Sprite* sprite);

	void RightloadWingFrames();
	void RightWingAnimation();

	void LeftloadWingFrames();
	void LeftWingAnimation();

	void loadSparkFrames();
	void updateSparkAnimation();

	void loadRightWalkFrames();
	void updateRightWalkAnimation();

	void loadLeftWalkFrames();
	void updateLeftWalkAnimation();

	void superSaiyanFrames();
	void superSaiyanAnimation();
};
#endif // ANIMATION_H