#include "Character.h"
#include <iostream>


sf::Sprite& Character::getSprite() {
    return *dragonSprite;
}

// 생성자에서 애니메이션, 텍스처, 사운드 로드
Character::Character() {
    linkAnimation();
    loadTextures();
}

Character::~Character() {
    //animation 클래스에서 변수를 빌려오는 것이므로 delete하면 animation 쪽의 변수가
    //해제되기에 충돌난다. 따라서 delete를 쓰면 안된다.
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
    case DragonState::Rightkamehameha:
        animation.RightKamehameAnimation();
        /*if (animation.isAnimationFinished() && !readyToReturnIdle) {
            readyToReturnIdle = true;
            kameEndDelayClock.restart();  // 딜레이 시작
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
    //-> 이건 0.5초가 지나면 자연스레 보통의 상태로 돌아가게 하는 코드로 일단 현재는 필요없다

}

void Character::sky_handleInput() {
    // deltaTime 계산
    float deltaTime = clock.restart().asSeconds();

    // 지면 충돌 처리
    sf::FloatRect bounds = dragonSprite->getGlobalBounds();
    // 입력 처리
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
    //정리를 잘 한 상태에서 오른쪽,왼쪽은 구분이 잘되게 만들 수 있다.
    //즉 up 조건문안에서 right,left는 구분만 잘하면 된다.


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
    // 방향키 입력 처리

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
    //x의 끝은 800값의 초과이고 y의 끝은 600값의 초과이다
    //때문에 800을 초과하거나 600을 초과하는 값이 나올 때를 대비해서 그 때의 값들을 위치로 확실히 지정해놓고
    //그 위치값들을 지정한 후 기본값으로 설정하면 오른쪽키를 계속 누르고 있어도 모양은 변하지 않는다.
}

void Character::ground_handleInput() {
    // deltaTime 계산
    float deltaTime = clock.restart().asSeconds();

    // 지면 충돌 처리
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
        //shiled부분은 아예 따로 빼놓아야 한다 예를 들어 Right 조건안에다
        //그대로 써버릴 경우 Right버튼을 누르고 있는 상태에서 s를 눌러야지 방어 모션이 취해지기에
        //별도의 동작들은 반드시 구분해야 한다.
        //middleshieldcnt는 내가 아무동작도 하지 않았을 때 기본적인 방어를 하게 하는 것으로
        //시작하자마자 방어 모션을 취하는 것이다.
        //s키를 누른 상태에서 A키를 누르면 자동적으로 A키의 모션이 발동되면서 스파크가 일어나지만 이건 좀 고민해보자


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
    sf::Vector2f scale = dragonSprite->getScale(); // 현재 스케일 (0.1, 0.2)

    if (currentState == DragonState::Rightkamehameha)
        return pos + sf::Vector2f(670.f * scale.x, 325.f * scale.y); // 오른쪽에서 날리므로 왼쪽 방향
    else if (currentState == DragonState::LeftKamehameha)
        return pos + sf::Vector2f(294.f * scale.x, 325.f * scale.y); // 왼쪽에서 날리므로 오른쪽 방향
    else
        return pos + sf::Vector2f(294.f * scale.x, 325.f * scale.y); // 기본 위치
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
            animation.resetRightKamehameha();  // ← 이거 빠졌다면 추가
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