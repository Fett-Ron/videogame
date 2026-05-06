#include <iostream>
#include "Game/Game.hpp"

int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;

    Game& game = Game::getInstance();
    game.init();
    game.run();
    game.destroy();

    return 0;
}