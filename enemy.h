#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED



struct enemy1 {
    int x, speed, health;

    enemy1(int x, int speed, int health): x(x), speed(speed), health(std::min(health, 99)) {}

    bool operator < (const enemy1 &o) {
        return x < o.x;
    }

    bool die() {
        return health <= 0;
    }

    void move() {
        x += speed;
    }

    void damaged(int damage) {
        health -= damage;
    }
};



#endif // ENEMY_H_INCLUDED
