#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED



#include <tuple>
#include <vector>



struct button {
    bool big = 0;
    int x, y, z, t;
    const char *str;
    std::vector<std::tuple<int, int, int, const char*>> s;

    button(int x, int y, const char *str, std::vector<std::tuple<int, int, int, const char*>> s = {}):
        x(x), y(y), z(x + strlen(str) * 24 + 36), t(y + 64), str(str), s(s) {}

    bool touched(int mouse_x, int mouse_y) {
        return x <= mouse_x && mouse_x <= z && y <= mouse_y && mouse_y <= t;
    }

    void animation(int mouse_x, int mouse_y) {
        big = touched(mouse_x, mouse_y);
    }
};



#endif // BUTTON_H_INCLUDED
