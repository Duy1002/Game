#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED



struct tower {
    int x, y, type, price, range, damage, knockback_distance, loading_time, cnt;

    tower(int x, int y, int type): x(x), y(y), type(type), cnt(0) {
        switch (type) {
            case 1:
                price = 10, range = 180, damage = 1, knockback_distance = 0, loading_time = 60;
                break;
            case 2:
                price = 10, range = 180, damage = 1, knockback_distance = 40, loading_time = 75;
                break;
            case 3:
                price = 20, range = 120, damage = 1, knockback_distance = 0, loading_time = 10;
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
};



#endif // TOWER_H_INCLUDED
