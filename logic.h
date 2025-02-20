#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED



#include <SDL.h>
#include "enemy.h"
#include "bullet.h"
#include "tower.h"
#include "waves.h"
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>
#include <ctime>
#include <cstdlib>



namespace logic {
    float health_factor[] = {0.5, 1, 1.5, 1.5};
    float speed_factor[] = {1, 1, 1, 1.5};
    const char *difficulty_name[] = {"EASY", "NORMAL", "HARD", "IMPOSSIBLE"};
    bool grid[7][16];
    int next_round_x = 323, next_round_y = 92, next_round_z = 707, next_round_t = 142;
    int difficulty = 1, enemy_speed, lives, money, round, upcoming_enemy, time_between_enemy = 30, timer;
    size_t current_wave_ptr;
    std::vector<waves::enemy_info> current_wave;
    std::vector<std::tuple<int, int>> path;
    std::list<enemy1> e1;
    std::list<bullet1> b1;
    std::list<tower1> t1;

    bool enemy_still_alive() {
        return upcoming_enemy || e1.size();
    }

    bool collision(bullet1 b, enemy1 e) {
        return (b.x - std::get<0>(path[e.x])) * (b.x - std::get<0>(path[e.x])) + (b.y - std::get<1>(path[e.x])) * (b.y - std::get<1>(path[e.x])) <= 400;
    }

    bool clicked_next_round_button(int mouse_x, int mouse_y) {
        return next_round_x <= mouse_x && mouse_x <= next_round_z && next_round_y <= mouse_y && mouse_y <= next_round_t;
    }

    void next_round() {
        current_wave = waves::get_wave(round);
        current_wave_ptr = 0;
        timer = 0;
        for (size_t i = 0; i < current_wave.size(); ++i) upcoming_enemy += current_wave[i].number;
        ++round;
    }

    void set_difficulty(int x) {
        difficulty = x;
    }

    void spawn_enemy(int x, int health) {
        e1.emplace_back(x, enemy_speed, health * health_factor[difficulty]);
    }

    void place_tower1(int x, int y) {
        t1.emplace_back(x * 60 + 30, y * 60 + 120);
    }

    void spawn_bullet1(int x, int y, int damage, int target_x, int target_y) {
        b1.emplace_back(x, y, damage, target_x, target_y);
    }

    void init(bool new_grid[7][16]) {
        srand(time(NULL));
        enemy_speed = 2 * speed_factor[difficulty];
        lives = 20;
        money = 0;
        round = 0;
        upcoming_enemy = 0;
        current_wave.clear();
        path.clear();
        e1.clear();
        t1.clear();
        b1.clear();
        for (int i = 0; i < 7; ++i)
            for (int j = 0; j < 16; ++j)
                grid[i][j] = new_grid[i][j];
        int i = 0, j = 0, prev_i = 0, prev_j = 0;
        while (i != 6 || j != 15) {
            int next_i, next_j;
            if (i && grid[i - 1][j] == 1 && i - 1 != prev_i) {
                for (int k = i * 60; k > (i - 1) * 60; --k) path.emplace_back(j * 60 + 30, k + 120);
                next_i = i - 1, next_j = j;
            } else if (j && grid[i][j - 1] == 1 && j - 1 != prev_j) {
                for (int k = j * 60; k > (j - 1) * 60; --k) path.emplace_back(k + 30, i * 60 + 120);
                next_i = i, next_j = j - 1;
            } else if (i != 6 && grid[i + 1][j] == 1 && i + 1 != prev_i) {
                for (int k = i * 60; k < (i + 1) * 60; ++k) path.emplace_back(j * 60 + 30, k + 120);
                next_i = i + 1, next_j = j;
            } else {
                for (int k = j * 60; k < (j + 1) * 60; ++k) path.emplace_back(k + 30, i * 60 + 120);
                next_i = i, next_j = j + 1;
            }
            prev_i = i, prev_j = j;
            i = next_i, j = next_j;
        }
        place_tower1(5, 3);
    }

    int do_logic() {
        for (std::list<bullet1>::iterator i = b1.begin(); i != b1.end();) {
            i->move();
            if (i->in_grid()) ++i;
            else i = b1.erase(i);
        }
        for (std::list<enemy1>::iterator i = e1.begin(); i != e1.end();) {
            i->move();
            if ((size_t)i->x >= path.size()) {
                i = e1.erase(i);
                if (lives) --lives;
            } else {
                for (std::list<bullet1>::iterator j = b1.begin(); j != b1.end();) {
                    if (collision(*j, *i)) {
                        i->damaged(j->damage);
                        j = b1.erase(j);
                    } else {
                        ++j;
                    }
                }
                if (i->die()) {
                    i = e1.erase(i);
                    ++money;
                } else {
                    ++i;
                }
            }
        }
        e1.sort();
        for (std::list<tower1>::iterator i = t1.begin(); i != t1.end(); ++i) {
            bool no_enemy = 1;
            for (std::list<enemy1>::reverse_iterator j = e1.rbegin(); j != e1.rend(); ++j) {
                if (i->in_range(std::get<0>(path[j->x]), std::get<1>(path[j->x]))) {
                    no_enemy = 0;
                    i->load();
                    if (i->ready()) {
                        spawn_bullet1(i->x, i->y, i->damage, std::get<0>(path[j->x]), std::get<1>(path[j->x]));
                        i->reset();
                    }
                    break;
                }
            }
            if (no_enemy) i->reset();
        }
        if (current_wave_ptr < current_wave.size()) {
            ++timer;
            if (timer == time_between_enemy) {
                if (!current_wave[current_wave_ptr].number) {
                    ++current_wave_ptr;
                } else {
                    spawn_enemy(0, current_wave[current_wave_ptr].health);
                    --current_wave[current_wave_ptr].number;
                    --upcoming_enemy;
                }
                timer = 0;
            }
        }
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) return -1;
            SDL_MouseButtonEvent mouse_event = ev.button;
            if (mouse_event.button == SDL_BUTTON_LEFT) {
                int mouse_x = mouse_event.x, mouse_y = mouse_event.y;
                if (!enemy_still_alive() && clicked_next_round_button(mouse_x, mouse_y)) next_round();
            }
        }
        if (!lives) return 0;
        return 1;
    }
}



#endif // LOGIC_H_INCLUDED
