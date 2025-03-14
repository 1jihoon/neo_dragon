#include "Character.h"
#include <iostream>


sf::Sprite& Character::getSprite() {
    return *dragonSprite;
}

// 생성자에서 애니메이션, 텍스처, 사운드 로드
Character::Character() {
   
}

void Character::linkAnimation() {
    animation.RightloadWingFrames();
    animation.LeftloadWingFrames();
    animation.loadSparkFrames();
    animation.loadRightWalkFrames();
    animation.loadLeftWalkFrames();
    animation.superSaiyanFrames();
}


int Character::loadTextures() {
    if (!dragonTexture.loadFromFile("neo_prime_photone_stand_up_2_.bmp")) return -1;
    if (!rightflyingTexture.loadFromFile("rightwings_neo_prime.bmp")) return -1;
    if (!leftflyingTexture.loadFromFile("leftwings_neo_prime.bmp")) return -1;
    if (!RightshiledTexture.loadFromFile("neo_prime_photone_rightshiled.bmp")) return -1;
    if (!LeftshiledTexture.loadFromFile("neo_prime_photone_leftshiled.bmp")) return -1;

    // 캐릭터 스프라이트 설정
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
        dragonSprite -> setTexture(dragonTexture); // Idle 텍스처
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
    }
}

void Character::handleInput() {
    // deltaTime 계산
    float deltaTime = clock.restart().asSeconds();
    float speed = 300.0f; // 이동 속도 (픽셀/초)

    // 입력 처리
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        sound.WingSounds();
        dragonSprite -> move(sf::Vector2f(0, -speed * deltaTime));
        currentState = DragonState::RightFlying;
        middlecnt = 1;
        dragonSprite -> move(sf::Vector2f(0, -speed * deltaTime));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            rightcnt = 1;
            leftcnt = 0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            leftcnt = 1;
            rightcnt = 0;
            currentState = DragonState::LeftFlying;
        }

        ismovingup = true;
    }
    //정리를 잘 한 상태에서 오른쪽,왼쪽은 구분이 잘되게 만들 수 있다.
    //즉 up 조건문안에서 right,left는 구분만 잘하면 된다.


    else {
        ismovingup = false;
        if ((rightcnt == 1 && leftcnt == 0) || middlecnt == 1) {
            currentState = DragonState::rightflying;
        }

        if (leftcnt == 1 && rightcnt == 0) {
            currentState = DragonState::leftflying;
        }
    }

    if (!ismovingup) {
        dragonSprite -> move(sf::Vector2f(0, gravity * deltaTime));
    }
    // 방향키 입력 처리

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        dragonSprite -> move(sf::Vector2f(speed * deltaTime, 0));
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        dragonSprite -> move(sf::Vector2f(-speed * deltaTime, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        dragonSprite -> move(sf::Vector2f(0, speed * deltaTime));
    }


    // 지면 충돌 처리
    sf::FloatRect bounds = dragonSprite->getGlobalBounds();

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
    //x의 끝은 800값의 초과이고 y의 끝은 600값의 초과이다
    //때문에 800을 초과하거나 600을 초과하는 값이 나올 때를 대비해서 그 때의 값들을 위치로 확실히 지정해놓고
    //그 위치값들을 지정한 후 기본값으로 설정하면 오른쪽키를 계속 누르고 있어도 모양은 변하지 않는다.

    if (dragonSprite->getPosition().y + bounds.size.y > 600) {
        dragonSprite->setPosition(sf::Vector2f(dragonSprite ->getPosition().x, 600 - bounds.size.y));
        currentState = DragonState::Idle;
        midleshieldcnt = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            currentState = DragonState::Spark;
            sound.SparkSounds();

            if (!fireActive) {
                if (clock_2.getElapsedTime().asSeconds() >= fireTriggerTime) {
                    fireReady = true;
                }
            }
            //A키를 눌렀을 때 false인 fireActive를 true로 바꾸고 그 안에서 5초 이상의 시간을 잰다
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
            //else일때 A키를 누르지 않은 상태이고 이 안에서 스파크의 상태를 관리하는게 맞다
            //지금 fireTriggerTime이 5초이상일때 변하는 것인데 5초 미만일때까지는 스파크가 움직이고
            //그 움직일때의 소리는 나면서 A키를 누르지 않았을 때는 효과음이 나지 않아야 하므로
            //그 때는 확실하게 소리를 멈추면 A키를 누르면 소리가 나고 누르지 않으면 소리가 끊기게 할 수 있다.
        }
        //5초가 지나면 다시 fireActive를 true로 바꾸고 fireReady를 false로 지정한다

        if (fireActive) {
            currentState = DragonState::Body;
            cnt -= 1;
            sound.Sparkstop();
            sound.SuerSounds();
        }

        if (cnt == 0) {
            fireActive = false;
            currentState = DragonState::Idle;
            //5초동안의 초사이어인 모습이 끝나면 바로 풀림
            sound.SuperStop();
        }
        //초사이어인 변신상태에서 쓰는 기술

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            if (!sound.sparkSoundThink) {
                sound.WalkSounds();
            }
            currentState = DragonState::RightWalking;
            rightshieldcnt = 1;
            leftshieldcnt = 0;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                currentState = DragonState::Spark;
                sound.sparkSoundThink = true;
            }

            else {
                sound.sparkSoundThink = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            if (!sound.sparkSoundThink) {
                sound.WalkSounds();
            }
            currentState = DragonState::LeftWalking;
            leftshieldcnt = 1;
            rightshieldcnt = 0;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                currentState = DragonState::Spark;
                sound.sparkSoundThink = true;
            }

            else {
                sound.sparkSoundThink = false;
            }
        }

        if ((rightshieldcnt == 1 && leftshieldcnt == 0) || midleshieldcnt == 1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                currentState = DragonState::Rightshiled;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                    currentState = DragonState::Spark;
                }
            }
        }

        if (leftshieldcnt == 1 && rightshieldcnt == 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                currentState = DragonState::Leftshiled;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                    currentState = DragonState::Spark;
                }
            }
        }
        //shiled부분은 아예 따로 빼놓아야 한다 예를 들어 Right 조건안에다
        //그대로 써버릴 경우 Right버튼을 누르고 있는 상태에서 s를 눌러야지 방어 모션이 취해지기에
        //별도의 동작들은 반드시 구분해야 한다.
        //middleshieldcnt는 내가 아무동작도 하지 않았을 때 기본적인 방어를 하게 하는 것으로
        //시작하자마자 방어 모션을 취하는 것이다.
        //s키를 누른 상태에서 A키를 누르면 자동적으로 A키의 모션이 발동되면서 스파크가 일어나지만 이건 좀 고민해보자
    }
}