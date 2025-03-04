#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED



#include <SDL.h>
#include "menu_system.h"
#include "logic.h"
#include "sound.h"
#include <ctime>



namespace game {
    void game_loop() {
        menu_system::init();
        menu *previous_menu = NULL;
        menu *current_menu = menu_system::intro;
        SDL_Event e;
        while (true) {
            clock_t start = clock();
            int mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            int previous_menu_type;
            if (previous_menu == menu_system::playing) previous_menu_type = 1;
            else if (previous_menu == menu_system::are_you_sure || previous_menu == menu_system::game_over) previous_menu_type = 2;
            else previous_menu_type = 3;
            int current_menu_type;
            if (current_menu == menu_system::playing) current_menu_type = 1;
            else if (current_menu == menu_system::are_you_sure || current_menu == menu_system::game_over) current_menu_type = 2;
            else current_menu_type = 3;
            previous_menu = current_menu;
            if (current_menu == menu_system::playing) {
                if (previous_menu_type != current_menu_type && previous_menu_type == 3) sound::stop_music();
                sound::play(sound::battle_loop);
                logic::animation(mouse_x, mouse_y);
                graphic::reset_screen();
                graphic::draw_playing_screen(mouse_x, mouse_y);
                graphic::present();
                int game_state = logic::do_logic();
                switch (game_state) {
                    case -1:
                        return;
                    case 0:
                        current_menu = menu_system::game_over;
                        break;
                    case 2:
                        sound::play(sound::click_button);
                        current_menu = menu_system::are_you_sure;
                        break;
                    default: break;
                }
            } else {
                if (previous_menu_type != current_menu_type) {
                    if (previous_menu_type == 1) sound::pause_music();
                    else sound::stop_music();
                }
                if (current_menu_type == 3) sound::play(sound::preparing_for_battle);
                current_menu->animation(mouse_x, mouse_y);
                graphic::reset_screen();
                if (current_menu == menu_system::game_over) graphic::draw_game_over_screen();
                graphic::draw_menu(*current_menu);
                graphic::present();
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) return;
                    menu *next_menu = current_menu->next(e.button);
                    if (next_menu) current_menu = next_menu;
                }
                if (current_menu == menu_system::quit) return;
                else if (current_menu == menu_system::difficulty_easy) logic::set_difficulty(0);
                else if (current_menu == menu_system::difficulty_normal) logic::set_difficulty(1);
                else if (current_menu == menu_system::difficulty_hard) logic::set_difficulty(2);
                else if (current_menu == menu_system::difficulty_impossible) logic::set_difficulty(3);
                else if (current_menu == menu_system::level1) {
                    logic::init(0);
                    current_menu = menu_system::playing;
                } else if (current_menu == menu_system::level2) {
                    logic::init(1);
                    current_menu = menu_system::playing;
                } else if (current_menu == menu_system::level3) {
                    logic::init(2);
                    current_menu = menu_system::playing;
                } else if (current_menu == menu_system::level4) {
                    logic::init(3);
                    current_menu = menu_system::playing;
                }
            }
            int used_time = clock() - start;
            SDL_Delay(used_time > 33 ? 0 : 33 - used_time);
        }
    }
}



#endif // GAME_H_INCLUDED
