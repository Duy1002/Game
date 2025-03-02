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
    bool grid_level[][7][16] = {
        {
            {1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
            {1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1}
        },
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        }
    };
    int current_level;
    int best_score[][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    bool grid[7][16], has_tower[7][16];
    int next_round_x = 323, next_round_y = 92, next_round_z = 707, next_round_t = 142;
    int home_x = 1000, home_y = 526, home_z = 1080, home_t = 586;
    int tower1_x = 1000, tower1_y = 124, tower1_z = 1080, tower1_t = 214;
    int tower2_x = 1000, tower2_y = 248, tower2_z = 1080, tower2_t = 338;
    int tower3_x = 1000, tower3_y = 372, tower3_z = 1080, tower3_t = 462;
    bool home_big, tower1_big, tower2_big, tower3_big;
    bool holding_tower1, holding_tower2, holding_tower3;
    int difficulty = 1, enemy_speed, lives, money, round, upcoming_enemy, time_between_enemy = 30, timer;
    unsigned int current_wave_ptr;
    std::vector<waves::enemy_info> current_wave;
    std::vector<std::tuple<int, int>> path;
    std::list<enemy> e;
    std::list<bullet> b;
    std::vector<tower> t;

    bool enemy_still_alive() {
        return upcoming_enemy || e.size();
    }

    bool is_holding_tower() {
        return holding_tower1 || holding_tower2 || holding_tower3;
    }

    bool collision(bullet b, enemy e) {
        int x = std::get<0>(path[e.x]), y = std::get<1>(path[e.x]);
        return (b.x - x) * (b.x - x) + (b.y - y) * (b.y - y) <= 625;
    }

    bool touched_next_round_button(int mouse_x, int mouse_y) {
        return next_round_x <= mouse_x && mouse_x <= next_round_z && next_round_y <= mouse_y && mouse_y <= next_round_t;
    }

    bool touched_home_button(int mouse_x, int mouse_y) {
        return home_x <= mouse_x && mouse_x <= home_z && home_y <= mouse_y && mouse_y <= home_t;
    }

    bool touched_tower1_button(int mouse_x, int mouse_y) {
        return tower1_x <= mouse_x && mouse_x <= tower1_z && tower1_y <= mouse_y && mouse_y <= tower1_t;
    }

    bool touched_tower2_button(int mouse_x, int mouse_y) {
        return tower2_x <= mouse_x && mouse_x <= tower2_z && tower2_y <= mouse_y && mouse_y <= tower2_t;
    }

    bool touched_tower3_button(int mouse_x, int mouse_y) {
        return tower3_x <= mouse_x && mouse_x <= tower3_z && tower3_y <= mouse_y && mouse_y <= tower3_t;
    }

    void next_round() {
        current_wave = waves::get_wave(round);
        current_wave_ptr = 0;
        timer = 0;
        for (std::vector<waves::enemy_info>::iterator i = current_wave.begin(); i != current_wave.end(); ++i)
            upcoming_enemy += i->number;
        ++round;
    }

    void set_difficulty(int x) {
        difficulty = x;
    }

    void spawn_enemy(int health) {
        health *= health_factor[difficulty];
        if (!health) health = 1;
        int dice = rand() % 6;
        if (dice < 3) e.emplace_back(0, enemy_speed, health, 1);
        else if (dice < 5) e.emplace_back(0, enemy_speed, health, 2);
        else e.emplace_back(0, enemy_speed, health, 3);
    }

    bool in_grid(int mouse_x, int mouse_y) {
        return 0 <= mouse_x && mouse_x < 960 && 90 <= mouse_y && mouse_y < 510;
    }

    void place_tower(int mouse_x, int mouse_y, int type) {
        if (in_grid(mouse_x, mouse_y)) {
            int x = mouse_x / 60, y = (mouse_y - 90) / 60;
            if (!grid[y][x] && !has_tower[y][x]) {
                tower tmp(x * 60 + 30, y * 60 + 120, type);
                if (money >= tmp.price) {
                    money -= tmp.price;
                    has_tower[y][x] = 1;
                    t.emplace_back(tmp);
                }
            }
        }
    }

    void spawn_bullet(int x, int y, int damage, int knockback_distance, int type, int target_x, int target_y) {
        b.emplace_back(x, y, damage, knockback_distance, type, target_x, target_y);
    }

    void animation(int mouse_x, int mouse_y) {
        home_big = touched_home_button(mouse_x, mouse_y);
        tower1_big = touched_tower1_button(mouse_x, mouse_y);
        tower2_big = touched_tower2_button(mouse_x, mouse_y);
        tower3_big = touched_tower3_button(mouse_x, mouse_y);
    }

    void init(int level) {
        srand(time(NULL));
        current_level = level;
        enemy_speed = 2 * speed_factor[difficulty];
        lives = 20;
        money = 25;
        round = 0;
        upcoming_enemy = 0;
        home_big = tower1_big = tower2_big = tower3_big = 0;
        holding_tower1 = holding_tower2 = holding_tower3 = 0;
        current_wave.clear();
        path.clear();
        e.clear(), t.clear(), b.clear();
        for (int i = 0; i < 7; ++i) for (int j = 0; j < 16; ++j) {
            grid[i][j] = grid_level[level][i][j];
            has_tower[i][j] = 0;
        }
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
    }

    int do_logic() {
        for (std::list<bullet>::iterator i = b.begin(); i != b.end();) {
            i->move();
            if (i->in_grid()) ++i;
            else i = b.erase(i);
        }
        for (std::list<enemy>::iterator i = e.begin(); i != e.end();) {
            i->move();
            if ((size_t)i->x >= path.size()) {
                i = e.erase(i);
                if (lives) --lives;
            } else {
                for (std::list<bullet>::iterator j = b.begin(); j != b.end();) {
                    if (collision(*j, *i)) {
                        i->damaged(j->damage);
                        i->knockback(j->knockback_distance);
                        j = b.erase(j);
                    } else {
                        ++j;
                    }
                }
                if (i->die()) {
                    i = e.erase(i);
                    ++money;
                } else {
                    ++i;
                }
            }
        }
        for (std::vector<tower>::iterator i = t.begin(); i != t.end(); ++i) {
            bool no_enemy = 1;
            for (std::list<enemy>::reverse_iterator j = e.rbegin(); j != e.rend(); ++j) {
                int x = std::get<0>(path[j->x]), y = std::get<1>(path[j->x]);
                bool break_loop = 0;
                switch (i->type) {
                    case 1: {
                        if (i->in_range(x, y)) {
                            no_enemy = 0;
                            i->load();
                            if (i->ready()) {
                                spawn_bullet(i->x, i->y, i->damage, i->knockback_distance, i->type, x, y);
                                i->reset();
                            }
                            break_loop = 1;
                        }
                        break;
                    }
                    case 2: {
                        if (i->in_range(x, y)) {
                            no_enemy = 0;
                            i->load();
                            if (i->ready()) {
                                spawn_bullet(i->x, i->y, i->damage, i->knockback_distance, i->type, x, y);
                                i->reset();
                            }
                            break_loop = 1;
                        }
                        break;
                    }
                    case 3: {
                        if (i->in_range(x, y)) {
                            if (no_enemy) {
                                i->load();
                                no_enemy = 0;
                            }
                            if (!i->ready()) {
                                break_loop = 1;
                                break;
                            }
                            int dx = x > i->x ? x - i->x : i->x - x;
                            int dy = y > i->y ? y - i->y : i->y - y;
                            if (dx <= 5 || dy <= 5) {
                                spawn_bullet(i->x, i->y, i->damage, i->knockback_distance, i->type, i->x - 1, i->y);
                                spawn_bullet(i->x, i->y, i->damage, i->knockback_distance, i->type, i->x + 1, i->y);
                                spawn_bullet(i->x, i->y, i->damage, i->knockback_distance, i->type, i->x, i->y - 1);
                                spawn_bullet(i->x, i->y, i->damage, i->knockback_distance, i->type, i->x, i->y + 1);
                                i->reset();
                                break_loop = 1;
                            }
                        }
                        break;
                    }
                    default: break;
                }
                if (break_loop) break;
            }
            if (no_enemy) i->reset();
        }
        if (current_wave_ptr < current_wave.size()) {
            ++timer;
            if (timer == time_between_enemy) {
                if (!current_wave[current_wave_ptr].number) {
                    ++current_wave_ptr;
                } else {
                    spawn_enemy(current_wave[current_wave_ptr].health);
                    --current_wave[current_wave_ptr].number;
                    --upcoming_enemy;
                }
                timer = 0;
            }
        }
        e.sort();
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) return -1;
            SDL_MouseButtonEvent mouse_event = ev.button;
            if (mouse_event.button == SDL_BUTTON_LEFT) {
                int mouse_x = mouse_event.x, mouse_y = mouse_event.y;
                if (touched_home_button(mouse_x, mouse_y)) return 2;
                if (!enemy_still_alive() && touched_next_round_button(mouse_x, mouse_y)) {
                    next_round();
                } else if (touched_tower1_button(mouse_x, mouse_y)) {
                    holding_tower1 = 1;
                    holding_tower2 = holding_tower3 = 0;
                } else if (touched_tower2_button(mouse_x, mouse_y)) {
                    holding_tower2 = 1;
                    holding_tower1 = holding_tower3 = 0;
                } else if (touched_tower3_button(mouse_x, mouse_y)) {
                    holding_tower3 = 1;
                    holding_tower1 = holding_tower2 = 0;
                } else if (holding_tower1) {
                    place_tower(mouse_x, mouse_y, 1);
                    holding_tower1 = 0;
                } else if (holding_tower2) {
                    place_tower(mouse_x, mouse_y, 2);
                    holding_tower2 = 0;
                } else if (holding_tower3) {
                    place_tower(mouse_x, mouse_y, 3);
                    holding_tower3 = 0;
                }
            }
        }
        if (!lives) {
            int current_best = best_score[current_level][difficulty];
            best_score[current_level][difficulty] = current_best > round ? current_best : round;
            return 0;
        }
        return 1;
    }
}



#endif // LOGIC_H_INCLUDED
