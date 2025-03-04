#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED



#include <vector>
#include <tuple>
#include "button.h"
#include "sound.h"



struct menu {
    std::vector<std::tuple<int, int, int, int>> rect;
    std::vector<std::tuple<button, menu*>> b;
    std::vector<std::tuple<int, int, int, const char*>> s;

    void animation(int mouse_x, int mouse_y) {
        for (std::vector<std::tuple<button, menu*>>::iterator i = b.begin(); i != b.end(); ++i)
            std::get<0>(*i).animation(mouse_x, mouse_y);
    }

    menu* next(SDL_MouseButtonEvent mouse_event) {
        if (mouse_event.button == SDL_BUTTON_LEFT)
            for (std::vector<std::tuple<button, menu*>>::iterator i = b.begin(); i != b.end(); ++i)
                if (std::get<0>(*i).touched(mouse_event.x, mouse_event.y)) {
                    menu *res = std::get<1>(*i);
                    if (res) sound::play(sound::click_button);
                    return res;
                }
        return NULL;
    }
};



#endif // MENU_H_INCLUDED
