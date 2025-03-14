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
        //�̰ɷ� ���������� 300�и��ʷ� ��� �ϸ� �޶����� ������ �߿��Ѱ�
        //������ �����鼭 �Ҹ��� ������ �����°� �߿��Ѱ��̹Ƿ� �ذ�ƴٰ�� �� �� ����
        wingSound->setPitch(1.8f);
        //�� ȿ������ �ӵ��� �����ϱ� ���� setPitch �Լ��� ��� ���ڰ� Ŀ������
        //�ӵ��� ��������.
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
