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
    Leftshiled
};

class Character{

private:
    sf::Sprite *dragonSprite = nullptr;
    sf::Texture dragonTexture;

    DragonState currentState = DragonState::Idle;
    Animation animation;
    Sound sound;

    // ��Ÿ ����

    float gravity = 200.0f; // �߷�
    sf::Clock clock;        // deltaTime ����

    int middlecnt = 0;
    int rightcnt = 0;
    int leftcnt = 0;
    bool ismovingup = false;

    int cnt = 0;
    bool fireReady = false;
    bool fireActive = false;

    sf::Clock clock_2;
    float fireTriggerTime = 5.0f;

    //������,���� ��� ����
    int rightshieldcnt = 0, leftshieldcnt = 0;
    int midleshieldcnt = 0;
    sf::Texture rightflyingTexture, bodyTexture, rightbodyTexture, sparkTexture, leftflyingTexture, RightshiledTexture, LeftshiledTexture;
    

public:
    Character();
    //dragon �̹����� public���� ���� �ʴ´ٸ� ���� �Լ����� �� �� ���⿡ �ݵ�� private��
    //���� �ȵȴ�.(���� ��ü�� ���� ���� �ֱ� �����̴�.)
    int loadTextures();

    void update();
    void handleInput();
    void linkAnimation();
    sf::Sprite& getSprite();  // �ܺο��� �׸����
};
#endif