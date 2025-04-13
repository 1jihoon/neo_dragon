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
//�� ���� �� �� �ʱ�ȭ �� ������ �ʱ� ���¿��� ���� ����

Animation::~Animation() {
    // �� �ʿ������� ������, ��������� ���� clear ����
    // ���� ���� ��� �� �� clear()�� ����.
    /*rightwingFrames.clear();
    leftwingFrames.clear();
    sparkFrames.clear();
    rightWalkFrames.clear();
    leftWalkFrames.clear();
    supersaiyanFrames.clear();
    RightkamehamehaFrames.clear();
    LeftkamehamehaFrames.clear();*/

    //���� ���� ��� �� clear()�� ������ �޸𸮴� �״�� ���⿡ 
    //�޸𸮸� ������ 0���� ������� �� swap�� �Ἥ �޸𸮸� ȸ���Ѵ�.
    std::vector<sf::Texture>().swap(rightwingFrames);
    std::vector<sf::Texture>().swap(leftwingFrames);
    std::vector<sf::Texture>().swap(sparkFrames);
    std::vector<sf::Texture>().swap(rightWalkFrames);
    std::vector<sf::Texture>().swap(leftWalkFrames);
    std::vector<sf::Texture>().swap(supersaiyanFrames);
    std::vector<sf::Texture>().swap(RightkamehamehaFrames);
    std::vector<sf::Texture>().swap(LeftkamehamehaFrames);

    delete targetSprite;
    //�����ͷ� Sprite�� ���������� �޸𸮰� ���õ����� �������ش�.
    //new sf�� targetSprite->setTexture(...)�� ���� ��������� delete�� �ᵵ ������
    //�ƴ϶�� ���� �ȵȴ�.
}

void Animation::setTargetSprite(sf::Sprite* sprite) {
    targetSprite = sprite;
}

// �ʱ�ȭ �Լ���
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
    RightkamehamehaFrames.clear();  // �ߺ� ����

    for (int i = 1; i <= 2; i++) {
        sf::Texture frame;
        std::string filename = "neo_prime_photone_Rightenergypa_" + std::to_string(i) + ".bmp";
        if (frame.loadFromFile(filename)){
            RightkamehamehaFrames.push_back(frame);
        }
    }
}

void Animation::LeftKamehameFrames() {
    LeftkamehamehaFrames.clear();  // �ߺ� ����

    for (int i = 1; i <= 2; i++) {
        sf::Texture frame;
        std::string filename = "neo_prime_photone_Leftenergypa_" + std::to_string(i) + ".bmp";
        if (frame.loadFromFile(filename)) {
            LeftkamehamehaFrames.push_back(frame);
        }
    }
}

void Animation::resetRightKamehameha() {
    RightkamehamehaFrame = -1; // ������ �ʱ�ȭ
    animationFinished = false;
    if (!RightkamehamehaFrames.empty()) {
        targetSprite->setTexture(RightkamehamehaFrames[0]);
        RightkamehameClock.restart(); // �ִϸ��̼� Ÿ�ֵ̹� �ʱ�ȭ
    }
}

void Animation::resetLeftKamehameha() {
    LeftkamehamehaFrame = -1; // ������ �ʱ�ȭ
    animationFinished = false; // �̰� ��������� false
    if (!LeftkamehamehaFrames.empty()) {
        targetSprite->setTexture(LeftkamehamehaFrames[0]);
        LeftkamehamehaClock.restart();
    }
}


// �ִϸ��̼� ������Ʈ �Լ���
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
        //std::cout << "[RightKamehameha] ������: " << RightkamehamehaFrame << std::endl;
        //std::cout << "���� ������: " << RightkamehamehaFrame << std::endl;
    }

    if (!animationFinished && RightkamehamehaFrame == RightkamehamehaFrames.size() - 1) {
        animationFinished = true;
        animationEndDelayClock.restart(); // �� ���� �ʱ�ȭ
        //std::cout << "[RightKamehameha] �ִϸ��̼� ����\n";
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
        animationEndDelayClock.restart(); // �� ���� �ʱ�ȭ
        //std::cout << "[LeftKamehameha] �ִϸ��̼� ����\n";
    }
}


bool Animation::isAnimationFinished() const {
    return animationFinished;
}

void Animation::resetAnimationFinished() {
    animationFinished = false;
}