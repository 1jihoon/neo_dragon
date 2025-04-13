#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Sound.h"

// �ִϸ��̼� ���� ����
enum class DragonState {
    Idle,//�⺻ ����
    RightFlying,//���������� �� ���� ����
    LeftFlying,//�������� �� ���� ����
    Spark,//����ũ ����
    RightWalking,//���������� �ȴ� ����
    LeftWalking,//�������� �ȴ� ����
    rightflying,//���������� ���ٰ� �ƹ��͵� ������ �ʾ��� ���� ����
    leftflying,//�������� ���ٰ� �ƹ��͵� ������ �ʾ��� ���� ����
    Body,//������������ ����
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

    // ��Ÿ ����

    float gravity = 200.0f; // �߷�
    sf::Clock clock;        // deltaTime ����

    bool ismovingup = false;

    int cnt = 0;
    bool fireReady = false;
    bool fireActive = false;

    sf::Clock clock_2;
    float fireTriggerTime = 5.0f;

    //������,���� ����
    int right = 0, left = 0;
    int middle = 0;
    
    sf::Texture rightflyingTexture, bodyTexture, rightbodyTexture, leftflyingTexture, RightshiledTexture, LeftshiledTexture;

public:
    Character();
    //dragon �̹����� public���� ���� �ʴ´ٸ� ���� �Լ����� �� �� ���⿡ �ݵ�� private��
    //���� �ȵȴ�.(���� ��ü�� ���� ���� �ֱ� �����̴�.)

    virtual ~Character();
    //������ ������ �ڷ����� ������� ��� �Ҹ��ڸ� ȣ���Ϸ��� virtual(���� �Ҹ���)�� ����.
    int loadTextures();

    void update();
    void handleInput();
    void sky_handleInput();
    void ground_handleInput();
    void linkAnimation();
    DragonState getCurrentState();
    void setCurrentState(DragonState state);

    sf::Vector2f getEnergyBallPosition();
    sf::Sprite& getSprite();  // �ܺο��� �׸����
};
#endif