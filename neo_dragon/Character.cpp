#include "Character.h"
#include <iostream>


sf::Sprite& Character::getSprite() {
    return *dragonSprite;
}

// �����ڿ��� �ִϸ��̼�, �ؽ�ó, ���� �ε�
Character::Character() {
    linkAnimation();
    loadTextures();
}

Character::~Character() {
    //animation Ŭ�������� ������ �������� ���̹Ƿ� delete�ϸ� animation ���� ������
    //�����Ǳ⿡ �浹����. ���� delete�� ���� �ȵȴ�.
}

void Character::linkAnimation() {
    animation.RightloadWingFrames();
    animation.LeftloadWingFrames();
    animation.loadSparkFrames();
    animation.loadRightWalkFrames();
    animation.loadLeftWalkFrames();
    animation.superSaiyanFrames();
    animation.RightKamehameFrames();
    animation.LeftKamehameFrames();
}


int Character::loadTextures() {
    if (!dragonTexture.loadFromFile("neo_prime_photone_stand_up_2_.bmp")) return -1;
    if (!rightflyingTexture.loadFromFile("rightwings_neo_prime.bmp")) return -1;
    if (!leftflyingTexture.loadFromFile("leftwings_neo_prime.bmp")) return -1;
    if (!RightshiledTexture.loadFromFile("neo_prime_photone_rightshiled.bmp")) return -1;
    if (!LeftshiledTexture.loadFromFile("neo_prime_photone_leftshiled.bmp")) return -1;

    // ĳ���� ��������Ʈ ����
    dragonSprite = new sf::Sprite(dragonTexture);
    dragonSprite -> setPosition(sf::Vector2f(0, 500));
    dragonSprite -> setScale(sf::Vector2f(0.1f, 0.2f));
    animation.setTargetSprite(dragonSprite);

    return 0;
}


void Character::update() {

    switch (currentState) {
    case DragonState::RightFlying:
        animation.RightWingAnimation();
        break;
    case DragonState::LeftFlying:
        animation.LeftWingAnimation();
        break;
    case DragonState::Spark:
        animation.updateSparkAnimation();
        break;
    case DragonState::RightWalking:
        animation.updateRightWalkAnimation();
        break;
    case DragonState::LeftWalking:
        animation.updateLeftWalkAnimation();
        break;
    case DragonState::rightflying:
        dragonSprite -> setTexture(rightflyingTexture);
        break;
    case DragonState::leftflying:
        dragonSprite -> setTexture(leftflyingTexture);
        break;
    case DragonState::Idle:
        dragonSprite -> setTexture(dragonTexture); // Idle �ؽ�ó
        break;
    case DragonState::Body:
        animation.superSaiyanAnimation();
        break;
    case DragonState::Rightshiled:
        dragonSprite -> setTexture(RightshiledTexture);
        break;
    case DragonState::Leftshiled:
        dragonSprite -> setTexture(LeftshiledTexture);
        break;
    case DragonState::Rightkamehameha:
        animation.RightKamehameAnimation();
        /*if (animation.isAnimationFinished() && !readyToReturnIdle) {
            readyToReturnIdle = true;
            kameEndDelayClock.restart();  // ������ ����
        }*/
        break;
    case DragonState::LeftKamehameha:
        animation.LeftKamehameAnimation();
        break;
    }

    /*if (readyToReturnIdle && kameEndDelayClock.getElapsedTime().asSeconds() > 0.5f) {
        setCurrentState(DragonState::Idle);
        animation.resetAnimationFinished();
        readyToReturnIdle = false;
    }*/ 
    //-> �̰� 0.5�ʰ� ������ �ڿ����� ������ ���·� ���ư��� �ϴ� �ڵ�� �ϴ� ����� �ʿ����

}

void Character::sky_handleInput() {
    // deltaTime ���
    float deltaTime = clock.restart().asSeconds();

    // ���� �浹 ó��
    sf::FloatRect bounds = dragonSprite->getGlobalBounds();
    // �Է� ó��
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        sound.WingSounds();
        sound.SuperStop();
        sound.Sparkstop();
        dragonSprite->move(sf::Vector2f(0, -speed * deltaTime));
        currentState = DragonState::RightFlying;
        middle = 1;
        dragonSprite->move(sf::Vector2f(0, -speed * deltaTime));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            right = 1;
            left = 0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            left = 1;
            right = 0;
            currentState = DragonState::LeftFlying;
        }

        ismovingup = true;
    }
    //������ �� �� ���¿��� ������,������ ������ �ߵǰ� ���� �� �ִ�.
    //�� up ���ǹ��ȿ��� right,left�� ���и� ���ϸ� �ȴ�.


    else {
        ismovingup = false;
        if ((right == 1 && left == 0) || middle == 1) {
            currentState = DragonState::rightflying;
        }

        if (left == 1 && right == 0) {
            currentState = DragonState::leftflying;
        }
    }

    if (!ismovingup) {
        dragonSprite->move(sf::Vector2f(0, gravity * deltaTime));
    }
    // ����Ű �Է� ó��

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        dragonSprite->move(sf::Vector2f(speed * deltaTime, 0));
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        dragonSprite->move(sf::Vector2f(-speed * deltaTime, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        dragonSprite->move(sf::Vector2f(0, speed * deltaTime));
    }


    if (dragonSprite->getPosition().x < 0)
        dragonSprite->setPosition(sf::Vector2f(0, dragonSprite->getPosition().y));

    if (dragonSprite->getPosition().y < 0)
        dragonSprite->setPosition(sf::Vector2f(dragonSprite->getPosition().x, 0));

    if (dragonSprite->getPosition().x + bounds.size.x > 800) {
        dragonSprite->setPosition(sf::Vector2f(800 - bounds.size.x, dragonSprite->getPosition().y));
        /*if (dragonSprite->getPosition().y + bounds.size.y <= 600) {
            currentState = DragonState::rightflying;
        }

        if (dragonSprite->getPosition().y + bounds.size.y > 600) {
            dragonSprite->setPosition(sf::Vector2f(800 - bounds.size.x, 600 - bounds.size.y));
            currentState = DragonState::Idle;
        }*/
    }
    //x�� ���� 800���� �ʰ��̰� y�� ���� 600���� �ʰ��̴�
    //������ 800�� �ʰ��ϰų� 600�� �ʰ��ϴ� ���� ���� ���� ����ؼ� �� ���� ������ ��ġ�� Ȯ���� �����س���
    //�� ��ġ������ ������ �� �⺻������ �����ϸ� ������Ű�� ��� ������ �־ ����� ������ �ʴ´�.
}

void Character::ground_handleInput() {
    // deltaTime ���
    float deltaTime = clock.restart().asSeconds();

    // ���� �浹 ó��
    sf::FloatRect bounds = dragonSprite->getGlobalBounds();

    if (dragonSprite->getPosition().y + bounds.size.y > 600) {
        dragonSprite->setPosition(sf::Vector2f(dragonSprite->getPosition().x, 600 - bounds.size.y));
        currentState = DragonState::Idle;
        middle = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            currentState = DragonState::Spark;
            sound.SparkSounds();

            if (!fireActive) {
                if (clock_2.getElapsedTime().asSeconds() >= fireTriggerTime) {
                    fireReady = true;
                }
            }
            //AŰ�� ������ �� false�� fireActive�� true�� �ٲٰ� �� �ȿ��� 5�� �̻��� �ð��� ���
            cnt += 1;
        }


        else {
            if (fireReady) {
                fireActive = true;
                fireReady = false;
            }
            clock_2.restart();

            if (fireReady == false) {
                sound.Sparkstop();
            }
            //else�϶� AŰ�� ������ ���� �����̰� �� �ȿ��� ����ũ�� ���¸� �����ϴ°� �´�
            //���� fireTriggerTime�� 5���̻��϶� ���ϴ� ���ε� 5�� �̸��϶������� ����ũ�� �����̰�
            //�� �����϶��� �Ҹ��� ���鼭 AŰ�� ������ �ʾ��� ���� ȿ������ ���� �ʾƾ� �ϹǷ�
            //�� ���� Ȯ���ϰ� �Ҹ��� ���߸� AŰ�� ������ �Ҹ��� ���� ������ ������ �Ҹ��� ����� �� �� �ִ�.
        }
        //5�ʰ� ������ �ٽ� fireActive�� true�� �ٲٰ� fireReady�� false�� �����Ѵ�

        if (fireActive) {
            currentState = DragonState::Body;
            cnt -= 1;
            sound.Sparkstop();
            sound.SuerSounds();
        }

        if (cnt == 0) {
            fireActive = false;
            currentState = DragonState::Idle;
            //5�ʵ����� �ʻ��̾��� ����� ������ �ٷ� Ǯ��
            sound.SuperStop();
        }
        //�ʻ��̾��� ���Ż��¿��� ���� ���

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            if (!sound.sparkSoundThink) {
                sound.WalkSounds();
            }
            currentState = DragonState::RightWalking;
            right = 1;
            left = 0;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                currentState = DragonState::Spark;
                sound.Wingstop();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            if (!sound.sparkSoundThink) {
                sound.WalkSounds();
            }
            currentState = DragonState::LeftWalking;
            left = 1;
            right = 0;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                currentState = DragonState::Spark;
                sound.Wingstop();
            }
        }

        if ((right == 1 && left == 0) || middle == 1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                currentState = DragonState::Rightshiled;
                sound.Sparkstop();
                sound.Wingstop();
                fireActive = false;
                fireReady = false;
            }
        }

        if (left == 1 && right == 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                currentState = DragonState::Leftshiled;
                sound.Sparkstop();
                sound.Wingstop();
                fireActive = false;
                fireReady = false;
            }

        }
        //shiled�κ��� �ƿ� ���� �����ƾ� �Ѵ� ���� ��� Right ���Ǿȿ���
        //�״�� ����� ��� Right��ư�� ������ �ִ� ���¿��� s�� �������� ��� ����� �������⿡
        //������ ���۵��� �ݵ�� �����ؾ� �Ѵ�.
        //middleshieldcnt�� ���� �ƹ����۵� ���� �ʾ��� �� �⺻���� �� �ϰ� �ϴ� ������
        //�������ڸ��� ��� ����� ���ϴ� ���̴�.
        //sŰ�� ���� ���¿��� AŰ�� ������ �ڵ������� AŰ�� ����� �ߵ��Ǹ鼭 ����ũ�� �Ͼ���� �̰� �� ����غ���


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && (right == 1)) {
            currentState = DragonState::Rightkamehameha;
            sound.Wingstop();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && (left == 1)) {
            currentState = DragonState::LeftKamehameha;
            sound.Wingstop();
        }

    }
}

sf::Vector2f Character::getEnergyBallPosition() {
    sf::Vector2f pos = dragonSprite->getPosition();
    sf::Vector2f scale = dragonSprite->getScale(); // ���� ������ (0.1, 0.2)

    if (currentState == DragonState::Rightkamehameha)
        return pos + sf::Vector2f(670.f * scale.x, 325.f * scale.y); // �����ʿ��� �����Ƿ� ���� ����
    else if (currentState == DragonState::LeftKamehameha)
        return pos + sf::Vector2f(294.f * scale.x, 325.f * scale.y); // ���ʿ��� �����Ƿ� ������ ����
    else
        return pos + sf::Vector2f(294.f * scale.x, 325.f * scale.y); // �⺻ ��ġ
}

DragonState Character::getCurrentState() {
    return currentState;
}

void Character::setCurrentState(DragonState state) {
    if (currentState != state) {
        currentState = state;
        readyToReturnIdle = false;
        //animation.resetAnimationFinished();

        if (state == DragonState::Rightkamehameha) {
            animation.resetRightKamehameha();  // �� �̰� �����ٸ� �߰�
        }
        else if (state == DragonState::LeftKamehameha) {
            animation.resetLeftKamehameha();
        }
    }
}



void Character::handleInput() {
    sky_handleInput();
    ground_handleInput();
}