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
}
//한 번에 싹 다 초기화

Animation::~Animation() {

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
        else {
            std::cerr << "Error: 파일 로드 실패 - " << filename << std::endl;
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
        else {
            std::cerr << "Error: 파일 로드 실패 - " << filename << std::endl;
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
        else {
            std::cerr << "Error: 파일 로드 실패 - " << filename << std::endl;
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
        else {
            std::cerr << "Error: 파일 로드 실패 - " << filename << std::endl;
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
        else {
            std::cerr << "Error: 파일 로드 실패 - " << filename << std::endl;
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

