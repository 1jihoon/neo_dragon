#include <iostream>
#include "Game.h"


//������� Charater.h�� �� �ڵ�
sf::Music backgroundMusic;
Game game;

// ���� �Լ�
int main() {

    // ��� ���� �ε�
    if (!backgroundMusic.openFromFile("Zexal-Sound-Duel-4-Barian_s-Force.ogg")) return -1;
    backgroundMusic.setLooping(true);
    backgroundMusic.play();
    
    game.run();
    
    return 0;
}