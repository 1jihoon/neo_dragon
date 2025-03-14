#include "Sound.h"

Sound::Sound() {
    loadSounds();
}

Sound::~Sound() {}

int Sound::loadSounds() {
    if (!wingSoundBuffer.loadFromFile("neo_prime_photon_wing.ogg")) return -1;
    if (!sparkSoundBuffer.loadFromFile("spark.ogg")) return -1;
    if (!superSoundBuffer.loadFromFile("short_fire.ogg")) return -1;

    wingSound = std::make_unique<sf::Sound>(wingSoundBuffer);
    sparkSound = std::make_unique<sf::Sound>(sparkSoundBuffer);
    superSound = std::make_unique<sf::Sound>(superSoundBuffer);
}

void Sound::WingSounds(){
    if (wingSound -> getStatus() != sf::SoundSource::Status::Playing) {
        wingSound->setBuffer(wingSoundBuffer);
        //wingSound.setPlayingOffset(sf::milliseconds(300.f));
        //이걸로 시작지점을 300밀리초로 잡고 하면 달라지긴 하지만 중요한건
        //완전히 나오면서 소리가 빠르게 나오는게 중요한것이므로 해결됐다고는 할 수 없다
        wingSound->setPitch(1.8f);
        //내 효과음의 속도를 조절하기 위해 setPitch 함수를 썼고 숫자가 커질수록
        //속도가 빨라진다.
        wingSound->play();
        wingSound->setVolume(300.f);
    }
}

void Sound::WalkSounds() {
    if (wingSound->getStatus() != sf::SoundSource::Status::Playing) {
        wingSound->setBuffer(wingSoundBuffer);
        wingSound->setPitch(1.5f);
        wingSound->play();
        wingSound->setVolume(220.f);
    }
}

void Sound::SparkSounds(){
    if (sparkSound -> getStatus() != sf::SoundSource::Status::Playing) {
        sparkSound -> setBuffer(sparkSoundBuffer);
        sparkSound->play();
        sparkSound->setVolume(150.f);
    }
}

void Sound::SuerSounds() {
    if (superSound -> getStatus() != sf::SoundSource::Status::Playing) {
        superSound->setBuffer(superSoundBuffer);
        superSound->play();
        superSound->setVolume(150.f);
    }
}

void Sound::Sparkstop() {
    sparkSound->stop();
}

void Sound::SuperStop() {
    superSound->stop();
}
