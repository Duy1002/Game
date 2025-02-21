#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED



#include <SDL.h>
#include <array>
#include "menu_system.h"
#include "logic.h"
#include <ctime>



namespace game {
    void game_loop() {
        menu_system::init();
        menu *current_menu = menu_system::intro;
        SDL_Event e;
        bool playing = 0;
        while (true) {
            clock_t start = clock();
            int mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            if (playing) {
                graphic::reset_screen();
                graphic::draw_playing_screen();
                graphic::present();
                int game_state = logic::do_logic();
                switch (game_state) {
                    case -1: return;
                    case 0:
                        playing = 0;
                        current_menu = menu_system::intro;
                        break;
                    default: break;
                }
            } else {
                current_menu->animation(mouse_x, mouse_y);
                graphic::reset_screen();
                graphic::draw_menu(*current_menu);
                graphic::present();
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) return;
                    menu *next_menu = current_menu->next(e.button);
                    if (next_menu) current_menu = next_menu;
                }
                if (current_menu == menu_system::quit) return;
                else if (current_menu == menu_system::difficulty_easy) {
                    logic::set_difficulty(0);
                    current_menu = menu_system::difficulty;
                } else if (current_menu == menu_system::difficulty_medium) {
                    logic::set_difficulty(1);
                    current_menu = menu_system::difficulty;
                } else if (current_menu == menu_system::difficulty_hard) {
                    logic::set_difficulty(2);
                    current_menu = menu_system::difficulty;
                }  else if (current_menu == menu_system::difficulty_impossible) {
                    logic::set_difficulty(3);
                    current_menu = menu_system::difficulty;
                } else if (current_menu == menu_system::level1) {
                    bool board[7][16] = {
                        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
                        {1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0},
                        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
                        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
                        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1}
                    };
                    logic::init(board);
                    playing = 1;
                } else if (current_menu == menu_system::level2) {
                    bool board[7][16] = {
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
                    };
                    logic::init(board);
                    playing = 1;
                } else if (current_menu == menu_system::level3) {
                    bool board[7][16] = {
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
                    };
                    logic::init(board);
                    playing = 1;
                } else if (current_menu == menu_system::level4) {
                    bool board[7][16] = {
                        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
                    };
                    logic::init(board);
                    playing = 1;
                }
            }
            SDL_Delay(std::max(33 - (int)(clock() - start), 0));
        }
    }
}



#endif // GAME_H_INCLUDED
