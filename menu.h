#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED



#include <SDL.h>
#include <vector>
#include <tuple>
#include "button.h"



struct menu {
    std::vector<std::tuple<int, int, int, int>> rect;
    std::vector<std::tuple<button, menu*>> b;
    std::vector<std::tuple<int, int, int, const char*>> s;

    void animation(int mouse_x, int mouse_y) {
        for (size_t i = 0; i < b.size(); ++i) std::get<0>(b[i]).animation(mouse_x, mouse_y);
    }

    menu* next(SDL_MouseButtonEvent mouse_event) {
        if (mouse_event.button == SDL_BUTTON_LEFT)
            for (size_t i = 0; i < b.size(); ++i)
                if (std::get<0>(b[i]).touched(mouse_event.x, mouse_event.y)) return std::get<1>(b[i]);
        return NULL;
    }
};



#endif // MENU_H_INCLUDED
