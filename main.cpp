#include "graphic.h"
#include "game.h"
#include "sound.h"


int main(int argc, char *argv[]) {
    graphic::init();
    sound::init();
    game::game_loop();
    sound::quit();
    graphic::quit_SDL();
    return 0;
}
