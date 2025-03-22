#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Sound.h"

// 애니메이션 상태 관리
enum class DragonState {
    Idle,//기본 상태
    RightFlying,//오른쪽으로 날 때의 상태
    LeftFlying,//왼쪽으로 날 때의 상태
    Spark,//스파크 상태
    RightWalking,//오른쪽으로 걷는 상태
    LeftWalking,//왼쪽으로 걷는 상태
    rightflying,//오른쪽으로 날다가 아무것도 누르지 않았을 때의 상태
    leftflying,//왼쪽으로 날다가 아무것도 누르지 않았을 때의 상태
    Body,//변신했을때의 상태
    Rightshiled,
    Leftshiled,
    Rightkamehameha,
    LeftKamehameha
};

class Character{

private:
    sf::Vector2f lastEnergyBallPosition;
    sf::Clock kameEndDelayClock;
    bool readyToReturnIdle = false;


    sf::Sprite *dragonSprite = nullptr;
    sf::Texture dragonTexture;

    DragonState currentState = DragonState::Idle;
    Animation animation;
    Sound sound;

    float speed = 300.0f;

    // 기타 변수

    float gravity = 200.0f; // 중력
    sf::Clock clock;        // deltaTime 계산용

    bool ismovingup = false;

    int cnt = 0;
    bool fireReady = false;
    bool fireActive = false;

    sf::Clock clock_2;
    float fireTriggerTime = 5.0f;

    //오른쪽,왼쪽 변수
    int right = 0, left = 0;
    int middle = 0;
    
    sf::Texture rightflyingTexture, bodyTexture, rightbodyTexture, leftflyingTexture, RightshiledTexture, LeftshiledTexture;

public:
    Character();
    //dragon 이미지는 public으로 하지 않는다면 메인 함수에서 쓸 수 없기에 반드시 private로
    //쓰면 안된다.(지금 객체로 만들어서 쓰고 있기 때문이다.)

    virtual ~Character();
    //포인터 변수의 자료형에 상관없이 모든 소멸자를 호출하려면 virtual(가상 소멸자)을 쓴다.
    int loadTextures();

    void update();
    void handleInput();
    void sky_handleInput();
    void ground_handleInput();
    void linkAnimation();
    DragonState getCurrentState();
    void setCurrentState(DragonState state);

    sf::Vector2f getEnergyBallPosition();
    sf::Sprite& getSprite();  // 외부에서 그리기용
};
#endif