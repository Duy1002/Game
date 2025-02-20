#include "graphic.h"
#include "game.h"



int main(int argc, char *argv[]) {
    graphic::init();
    game::game_loop();
    graphic::quit_SDL();
    return 0;
}
