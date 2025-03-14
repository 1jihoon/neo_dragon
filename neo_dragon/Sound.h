#pragma once

#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>

class Sound {
private:
      std::unique_ptr<sf::Sound> wingSound, sparkSound, superSound;
      sf::SoundBuffer wingSoundBuffer, sparkSoundBuffer, superSoundBuffer;

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
};

#endif
