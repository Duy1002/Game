#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED



#include <cmath>
#include "enemy.h"



struct bullet {
    float x, y, speed_x, speed_y;
    int damage, knockback_distance, type;

    bullet(int x, int y, int damage, int knockback_distance, int type, int target_x, int target_y): x(x), y(y), damage(damage), knockback_distance(knockback_distance), type(type) {
        float angle = std::atan(float(target_y - y) / float(target_x - x));
        speed_x = 20 * std::cos(angle);
        speed_y = 20 * std::sin(angle);
        if (target_x < x) speed_x = -speed_x, speed_y = -speed_y;
    }

    void move() {
        x += speed_x;
        y += speed_y;
    }

    bool in_grid() {
        return -10 <= x && x < 970 && 80 <= y && y < 520;
    }
};



#endif // BULLET_H_INCLUDED
