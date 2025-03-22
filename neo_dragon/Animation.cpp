#include "Animation.h"
#include <iostream>


Animation::Animation() {
    setTargetSprite(nullptr);
    RightloadWingFrames();
    LeftloadWingFrames();
    loadSparkFrames();
    loadRightWalkFrames();
    loadLeftWalkFrames();
    superSaiyanFrames();
    RightKamehameFrames();
    LeftKamehameFrames();
}
//한 번에 싹 다 초기화 즉 안전한 초기 상태에서 시작 가능

Animation::~Animation() {
    // 꼭 필요하지는 않지만, 명시적으로 벡터 clear 가능
    // 벡터 안을 비울 때 이 clear()를 쓴다.
    /*rightwingFrames.clear();
    leftwingFrames.clear();
    sparkFrames.clear();
    rightWalkFrames.clear();
    leftWalkFrames.clear();
    supersaiyanFrames.clear();
    RightkamehamehaFrames.clear();
    LeftkamehamehaFrames.clear();*/

    //벡터 안을 비울 때 clear()를 쓰지만 메모리는 그대로 남기에 
    //메모리를 완전히 0으로 만드려면 이 swap을 써서 메모리를 회수한다.
    std::vector<sf::Texture>().swap(rightwingFrames);
    std::vector<sf::Texture>().swap(leftwingFrames);
    std::vector<sf::Texture>().swap(sparkFrames);
    std::vector<sf::Texture>().swap(rightWalkFrames);
    std::vector<sf::Texture>().swap(leftWalkFrames);
    std::vector<sf::Texture>().swap(supersaiyanFrames);
    std::vector<sf::Texture>().swap(RightkamehamehaFrames);
    std::vector<sf::Texture>().swap(LeftkamehamehaFrames);

    delete targetSprite;
    //포인터로 Sprite를 선언했으니 메모리가 관련됐으니 해제해준다.
    //new sf나 targetSprite->setTexture(...)로 내가 만들었으면 delete를 써도 되지만
    //아니라면 쓰면 안된다.
}

void Animation::setTargetSprite(sf::Sprite* sprite) {
    targetSprite = sprite;
}

// 초기화 함수들
void Animation::RightloadWingFrames() {
    for (int i = 1; i <= 3; i++) {
        sf::Texture frame;
        std::string filename = "rightwings_" + std::to_string(i) + ".bmp";
        if (frame.loadFromFile(filename)) {
            rightwingFrames.push_back(frame);
        }
    }
}

void Animation::LeftloadWingFrames() {
    for (int i = 1; i <= 3; i++) {
        sf::Texture frame;
        std::string filename = "leftwings_" + std::to_string(i) + ".bmp";
        if (frame.loadFromFile(filename)) {
            leftwingFrames.push_back(frame);
        }
    }

}
void Animation::loadSparkFrames() {
    for (int i = 1; i <= 5; i++) {
        sf::Texture frame;
        std::string filename = "spark_" + std::to_string(i) + ".bmp";
        if (frame.loadFromFile(filename)) {
            sparkFrames.push_back(frame);
        }
    }
}
void Animation::loadRightWalkFrames() {
    for (int i = 1; i <= 4; i++) {
        sf::Texture frame;
        std::string filename = "rightwalking_" + std::to_string(i) + ".bmp";
        if (frame.loadFromFile(filename)) {
            rightWalkFrames.push_back(frame);
        }
    }
}
void Animation::loadLeftWalkFrames() {
    for (int i = 1; i <= 4; i++) {
        sf::Texture frame;
        std::string filename = "leftwalking_" + std::to_string(i) + ".bmp";
        if (frame.loadFromFile(filename)) {
            leftWalkFrames.push_back(frame);
        }
    }
}

void Animation::superSaiyanFrames() {
    for (int i = 1; i <= 5; i++) {
        sf::Texture frame;
        std::string filename = "neo_prime_photone_super_saiyan_2_" + std::to_string(i) + ".bmp";
        if (frame.loadFromFile(filename)) {
            supersaiyanFrames.push_back(frame);
        }
    }
}

void Animation::RightKamehameFrames() {
    RightkamehamehaFrames.clear();  // 중복 방지

    for (int i = 1; i <= 2; i++) {
        sf::Texture frame;
        std::string filename = "neo_prime_photone_Rightenergypa_" + std::to_string(i) + ".bmp";
        if (frame.loadFromFile(filename)){
            RightkamehamehaFrames.push_back(frame);
        }
    }
}

void Animation::LeftKamehameFrames() {
    LeftkamehamehaFrames.clear();  // 중복 방지

    for (int i = 1; i <= 2; i++) {
        sf::Texture frame;
        std::string filename = "neo_prime_photone_Leftenergypa_" + std::to_string(i) + ".bmp";
        if (frame.loadFromFile(filename)) {
            LeftkamehamehaFrames.push_back(frame);
        }
    }
}

void Animation::resetRightKamehameha() {
    RightkamehamehaFrame = -1; // 프레임 초기화
    animationFinished = false;
    if (!RightkamehamehaFrames.empty()) {
        targetSprite->setTexture(RightkamehamehaFrames[0]);
        RightkamehameClock.restart(); // 애니메이션 타이밍도 초기화
    }
}

void Animation::resetLeftKamehameha() {
    LeftkamehamehaFrame = -1; // 프레임 초기화
    animationFinished = false; // 이걸 명시적으로 false
    if (!LeftkamehamehaFrames.empty()) {
        targetSprite->setTexture(LeftkamehamehaFrames[0]);
        LeftkamehamehaClock.restart();
    }
}


// 애니메이션 업데이트 함수들
void Animation::RightWingAnimation() {
    if (RightwingClock.getElapsedTime().asSeconds() > frameDuration / animationSpeed) {
        rightwingFrame = (rightwingFrame + 1) % rightwingFrames.size();
        targetSprite->setTexture(rightwingFrames[rightwingFrame]);
        RightwingClock.restart();
    }
}

void Animation::LeftWingAnimation() {
    if (LeftwingClock.getElapsedTime().asSeconds() > frameDuration / animationSpeed) {
        leftwingFrame = (leftwingFrame + 1) % leftwingFrames.size();
        targetSprite->setTexture(leftwingFrames[leftwingFrame]);
        LeftwingClock.restart();
    }
}
void Animation::updateSparkAnimation() {
    if (sparkClock.getElapsedTime().asSeconds() > (sparkDuration / sparkSpeed) * 3) {
        sparkFrame = (sparkFrame + 1) % sparkFrames.size();
        targetSprite->setTexture(sparkFrames[sparkFrame]);
        sparkClock.restart();
    }
}
void Animation::updateRightWalkAnimation() {
    if (rightWalkClock.getElapsedTime().asSeconds() > rightWalkDuration / rightWalkSpeed) {
        rightWalkFrame = (rightWalkFrame + 1) % rightWalkFrames.size();
        targetSprite->setTexture(rightWalkFrames[rightWalkFrame]);
        rightWalkClock.restart();
    }
}
void Animation::updateLeftWalkAnimation() {
    //if (targetSprite == nullptr || leftWalkFrames.empty()) return;
    if (leftWalkClock.getElapsedTime().asSeconds() > leftWalkDuration / leftWalkSpeed) {
        leftWalkFrame = (leftWalkFrame + 1) % leftWalkFrames.size();
        targetSprite->setTexture(leftWalkFrames[leftWalkFrame]);
        leftWalkClock.restart();
    }
}

void Animation::superSaiyanAnimation() {
    if (superClock.getElapsedTime().asSeconds() > superDuration / superSpeed) {
        supersaiyanFrame = (supersaiyanFrame + 1) % supersaiyanFrames.size();
        targetSprite->setTexture(supersaiyanFrames[supersaiyanFrame]);
        superClock.restart();
    }
}

void Animation::RightKamehameAnimation() {
    if (RightkamehameClock.getElapsedTime().asSeconds() > RightkamehameDuration / RightkamehameSpeed) {
        RightkamehamehaFrame = (RightkamehamehaFrame + 1) % RightkamehamehaFrames.size();
        targetSprite->setTexture(RightkamehamehaFrames[RightkamehamehaFrame]);
        RightkamehameClock.restart();
        //std::cout << "[RightKamehameha] 프레임: " << RightkamehamehaFrame << std::endl;
        //std::cout << "현재 프레임: " << RightkamehamehaFrame << std::endl;
    }

    if (!animationFinished && RightkamehamehaFrame == RightkamehamehaFrames.size() - 1) {
        animationFinished = true;
        animationEndDelayClock.restart(); // 한 번만 초기화
        //std::cout << "[RightKamehameha] 애니메이션 종료\n";
    }
}

void Animation::LeftKamehameAnimation() {
    if (LeftkamehamehaClock.getElapsedTime().asSeconds() > LeftkamehameDuration / LeftkamehameSpeed) {
        LeftkamehamehaFrame = (LeftkamehamehaFrame + 1) % LeftkamehamehaFrames.size();
        targetSprite->setTexture(LeftkamehamehaFrames[LeftkamehamehaFrame]);
        LeftkamehamehaClock.restart();
    }

    if (!animationFinished && LeftkamehamehaFrame == LeftkamehamehaFrames.size() - 1) {
        animationFinished = true;
        animationEndDelayClock.restart(); // 한 번만 초기화
        //std::cout << "[LeftKamehameha] 애니메이션 종료\n";
    }
}


bool Animation::isAnimationFinished() const {
    return animationFinished;
}

void Animation::resetAnimationFinished() {
    animationFinished = false;
}