#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED



struct tower1 {
    int x, y, range = 210, damage = 1, loading_time = 30, cnt = 0;

    tower1(int x, int y): x(x), y(y) {}

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
