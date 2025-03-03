#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED



#define TOWER1_INIT_PRICE 10
#define TOWER1_INIT_RANGE 150
#define TOWER1_INIT_DAMAGE 1
#define TOWER1_INIT_KNOCKBACK_DISTANCE 0
#define TOWER1_INIT_LOADING_TIME 60
#define TOWER1_UPGRADE1_PRICE 10
#define TOWER1_UPGRADE2_PRICE 15
#define TOWER1_UPGRADED_RANGE 210
#define TOWER1_UPGRADED_DAMAGE 2

#define TOWER2_INIT_PRICE 10
#define TOWER2_INIT_RANGE 150
#define TOWER2_INIT_DAMAGE 1
#define TOWER2_INIT_KNOCKBACK_DISTANCE 40
#define TOWER2_INIT_LOADING_TIME 75
#define TOWER2_UPGRADE1_PRICE 10
#define TOWER2_UPGRADE2_PRICE 10
#define TOWER2_UPGRADED_RANGE 210
#define TOWER2_UPGRADED_KNOCKBACK_DISTANCE 70

#define TOWER3_INIT_PRICE 20
#define TOWER3_INIT_RANGE 90
#define TOWER3_INIT_DAMAGE 1
#define TOWER3_INIT_KNOCKBACK_DISTANCE 0
#define TOWER3_INIT_LOADING_TIME 10
#define TOWER3_UPGRADE1_PRICE 15
#define TOWER3_UPGRADE2_PRICE 25
#define TOWER3_UPGRADED_RANGE 150
#define TOWER3_UPGRADED_LOADING_TIME 2

#define SELL_PRICE_FACTOR 3/5



struct tower {
    int x, y, type, price, range, damage, knockback_distance, loading_time, cnt;
    bool upgraded1, upgraded2;

    tower(int x, int y, int type): x(x), y(y), type(type), cnt(0) {
        switch (type) {
            case 1:
                price = TOWER1_INIT_PRICE;
                range = TOWER1_INIT_RANGE;
                damage = TOWER1_INIT_DAMAGE;
                knockback_distance = TOWER1_INIT_KNOCKBACK_DISTANCE;
                loading_time = TOWER1_INIT_LOADING_TIME;
                upgraded1 = upgraded2 = 0;
                break;
            case 2:
                price = TOWER2_INIT_PRICE;
                range = TOWER2_INIT_RANGE;
                damage = TOWER2_INIT_DAMAGE;
                knockback_distance = TOWER2_INIT_KNOCKBACK_DISTANCE;
                loading_time = TOWER2_INIT_LOADING_TIME;
                upgraded1 = upgraded2 = 0;
                break;
            case 3:
                price = TOWER3_INIT_PRICE;
                range = TOWER3_INIT_RANGE;
                damage = TOWER3_INIT_DAMAGE;
                knockback_distance = TOWER3_INIT_KNOCKBACK_DISTANCE;
                loading_time = TOWER3_INIT_LOADING_TIME;
                upgraded1 = upgraded2 = 0;
                break;
            default: break;
        }
    }

    bool in_range(int target_x, int target_y) {
        return (x - target_x) * (x - target_x) + (y - target_y) * (y - target_y) <= range * range;
    }

    void reset() {
        cnt = 0;
    }

    void load() {
        ++cnt;
    }

    bool ready() {
        return cnt >= loading_time;
    }

    void upgrade1() {
        switch (type) {
            case 1:
                price += TOWER1_UPGRADE1_PRICE;
                range = TOWER1_UPGRADED_RANGE;
                break;
            case 2:
                price += TOWER2_UPGRADE1_PRICE;
                range = TOWER2_UPGRADED_RANGE;
                break;
            case 3:
                price += TOWER3_UPGRADE1_PRICE;
                range = TOWER3_UPGRADED_RANGE;
                break;
            default: break;
        }
        upgraded1 = 1;
    }

    void upgrade2() {
        switch (type) {
            case 1:
                price += TOWER1_UPGRADE2_PRICE;
                damage = TOWER1_UPGRADED_DAMAGE;
                break;
            case 2:
                price += TOWER2_UPGRADE2_PRICE;
                knockback_distance = TOWER2_UPGRADED_KNOCKBACK_DISTANCE;
                break;
            case 3:
                price += TOWER3_UPGRADE2_PRICE;
                loading_time = TOWER3_UPGRADED_LOADING_TIME;
                break;
            default: break;
        }
        upgraded2 = 1;
    }
};



#endif // TOWER_H_INCLUDED
