#include <iostream>
#include "Game.h"


//여기까지 Charater.h에 쓸 코드
sf::Music backgroundMusic;
Game game;

// 메인 함수
int main() {

    // 배경 음악 로드
    if (!backgroundMusic.openFromFile("Zexal-Sound-Duel-4-Barian_s-Force.ogg")) return -1;
    backgroundMusic.setLooping(true);
    backgroundMusic.play();
    
    game.run();
    
    return 0;
}