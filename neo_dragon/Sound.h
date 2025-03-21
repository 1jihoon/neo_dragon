#pragma once

#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>

class Sound {
private:
      std::unique_ptr<sf::Sound> wingSound, sparkSound, superSound;
      sf::SoundBuffer wingSoundBuffer, sparkSoundBuffer, superSoundBuffer;
      //sf::Sound 클래스가 복사 방지 클래스이기에 소유권을 넘겨주는 
      //unique_ptr을 써서 소유권을 넘겨주게 해야만 한다.
      //이렇게 함으로써 unique_ptr은 자동으로 메모리도 해제한다.

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
