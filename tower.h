#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED



struct tower {
    int x, y, type, price, range, damage, knockback_distance, loading_time, cnt;

    tower(int x, int y, int type): x(x), y(y), type(type), cnt(0) {
        switch (type) {
            case 1:
                price = 5, range = 150, damage = 1, knockback_distance = 0, loading_time = 60;
                break;
            case 2:
                price = 5, range = 150, damage = 0, knockback_distance = 70, loading_time = 60;
                break;
            case 3:
                price = 25, range = 90, damage = 1, knockback_distance = 0, loading_time = 15;
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
