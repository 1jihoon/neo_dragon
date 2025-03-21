#pragma once

#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>

class Sound {
private:
      std::unique_ptr<sf::Sound> wingSound, sparkSound, superSound;
      sf::SoundBuffer wingSoundBuffer, sparkSoundBuffer, superSoundBuffer;
      //sf::Sound Ŭ������ ���� ���� Ŭ�����̱⿡ �������� �Ѱ��ִ� 
      //unique_ptr�� �Ἥ �������� �Ѱ��ְ� �ؾ߸� �Ѵ�.
      //�̷��� �����ν� unique_ptr�� �ڵ����� �޸𸮵� �����Ѵ�.

public:
    Sound();
    virtual ~Sound();
    bool sparkSoundThink = false;

    int loadSounds();

    void SparkSounds();
    void WingSounds();
    void WalkSounds();
    void SuerSounds();

    void Sparkstop();
    void SuperStop();
    void Wingstop();
};

#endif
