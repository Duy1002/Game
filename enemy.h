#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED



struct enemy {
    int x, speed, health, type, init_health, health_health;

    enemy(int x, int _speed, int _health, int type): x(x), speed(_speed), health(_health < 99 ? _health : 99), type(type) {
        init_health = health;
        switch (type) {
            case 1:
                health_health = 1;
                break;
            case 2:
                health_health = 1;
                ++speed;
                break;
            case 3:
                health_health = 2;
                break;
            default: break;
        }
    }

    bool operator < (const enemy &o) {
        return x < o.x;
    }

    bool die() {
        return health_health <= 0;
    }

    void move() {
        x += speed;
    }

    void damaged(int damage) {
        health -= damage;
        if (health <= 0) {
            --health_health;
            health = init_health;
            switch (type) {
                case 3:
                    type = 1;
                    break;
                default: break;
            }
        }
    }

    void knockback(int distance) {
        x = x < distance ? 0 : x - distance;
    }
};



#endif // ENEMY_H_INCLUDED
