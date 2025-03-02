#ifndef WAVES_H_INCLUDED
#define WAVES_H_INCLUDED



#include <vector>



namespace waves {
    struct enemy_info {
        int number, health;
        enemy_info(int number, int health): number(number), health(health) {}
    };

    std::vector<std::vector<enemy_info>> waves = {
        std::vector<enemy_info>({
            enemy_info(5, 1)
        }),
        std::vector<enemy_info>({
            enemy_info(4, 1),
            enemy_info(2, 2)
        })
    };

    std::vector<enemy_info> get_wave(int round) {
        std::vector<enemy_info> res = waves[round % waves.size()];
        int add_health = round / waves.size();
        int add_number = add_health / 2;
        for (std::vector<waves::enemy_info>::iterator i = res.begin(); i != res.end(); ++i) {
            i->number += add_number;
            i->health += add_health;
        }
        return res;
    }
}



#endif // WAVES_H_INCLUDED
