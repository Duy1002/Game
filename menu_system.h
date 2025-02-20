#ifndef MENU_SYSTEM_H_INCLUDED
#define MENU_SYSTEM_H_INCLUDED



#include <vector>
#include <tuple>
#include "button.h"
#include "menu.h"



namespace menu_system {
    menu *quit = new menu();
    menu *intro = new menu();
    menu *difficulty = new menu();
    menu *difficulty_easy = new menu();
    menu *difficulty_medium = new menu();
    menu *difficulty_hard = new menu();
    menu *difficulty_impossible = new menu();
    menu *level_selection = new menu();
    menu *level1 = new menu();
    menu *level2 = new menu();
    menu *level3 = new menu();
    menu *level4 = new menu();

    void init() {
        intro->b =
        std::vector<std::tuple<button, menu*>>({
            std::make_tuple(
                button(494, 340, "PLAY"),
                level_selection
            ),
            std::make_tuple(
                button(422, 440, "DIFFICULTY"),
                difficulty
            ),
            std::make_tuple(
                button(494, 540, "EXIT"),
                quit
            )
        });
        intro->s =
        std::vector<std::tuple<int, int, int, const char*>>({
            std::make_tuple(328, 28, 16, "TOWER"),
            std::make_tuple(232, 160, 16, "DEFENSE")
        });

        difficulty->rect =
        std::vector<std::tuple<int, int, int, int>>({
            std::make_tuple(150, 0, 10, 150),
            std::make_tuple(150, 150, 830, 10),
            std::make_tuple(970, 0, 10, 150)
        });
        difficulty->b =
        std::vector<std::tuple<button, menu*>>({
            std::make_tuple(
                button(46, 534, "BACK"),
                intro
            ),
            std::make_tuple(
                button(267, 238, "EASY",
                    std::vector<std::tuple<int, int, int, const char*>>({
                        std::make_tuple(200, 25, 6, "ENEMY HEALTH x0.5"),
                        std::make_tuple(200, 90, 6, "ENEMY SPEED x1")
                    })
                ),
                difficulty_easy
            ),
            std::make_tuple(
                button(630, 238, "NORMAL",
                    std::vector<std::tuple<int, int, int, const char*>>({
                        std::make_tuple(200, 25, 6, "ENEMY HEALTH x1"),
                        std::make_tuple(200, 90, 6, "ENEMY SPEED x1")
                    })
                ),
                difficulty_medium
            ),
            std::make_tuple(
                button(267, 384, "HARD",
                    std::vector<std::tuple<int, int, int, const char*>>({
                        std::make_tuple(200, 25, 6, "ENEMY HEALTH x1.5"),
                        std::make_tuple(200, 90, 6, "ENEMY SPEED x1")
                    })
                ),
                difficulty_hard
            ),
            std::make_tuple(
                button(582, 384, "IMPOSSIBLE",
                    std::vector<std::tuple<int, int, int, const char*>>({
                        std::make_tuple(200, 25, 6, "ENEMY HEALTH x1.5"),
                        std::make_tuple(200, 90, 6, "ENEMY SPEED x1.5")
                    })
                ),
                difficulty_impossible
            )
        });

        level_selection->b =
        std::vector<std::tuple<button, menu*>>({
            std::make_tuple(
                button(46, 534, "BACK"),
                intro
            ),
            std::make_tuple(
                button(237, 238, "LEVEL 1"),
                level1
            ),
            std::make_tuple(
                button(679, 238, "LEVEL 2"),
                level2
            ),
            std::make_tuple(
                button(237, 384, "LEVEL 3"),
                level3
            ),
            std::make_tuple(
                button(679, 384, "LEVEL 4"),
                level4
            )
        });
        level_selection->s =
        std::vector<std::tuple<int, int, int, const char*>>({
            std::make_tuple(204, 50, 8, "LEVEL SELECTION")
        });
    }
};



#endif // MENU_SYSTEM_H_INCLUDED
