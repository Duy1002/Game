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
            enemy_info(6, 1)
        }),
        std::vector<enemy_info>({
            enemy_info(3, 2)
        }),
        std::vector<enemy_info>({
            enemy_info(5, 1),
            enemy_info(3, 2)
        }),
        std::vector<enemy_info>({
            enemy_info(3, 1),
            enemy_info(3, 3),
            enemy_info(3, 2)
        }),
        std::vector<enemy_info>({
            enemy_info(4, 2),
            enemy_info(5, 3)
        }),
        std::vector<enemy_info>({
            enemy_info(1, 2),
            enemy_info(4, 3),
            enemy_info(3, 4)
        }),
        std::vector<enemy_info>({
            enemy_info(3, 3),
            enemy_info(5, 4),
            enemy_info(1, 5)
        }),
        std::vector<enemy_info>({
            enemy_info(2, 5),
            enemy_info(2, 4),
            enemy_info(3, 6)
        }),
        std::vector<enemy_info>({
            enemy_info(4, 5),
            enemy_info(1, 7),
            enemy_info(4, 6)
        }),
        std::vector<enemy_info>({
            enemy_info(10, 7)
        })
    };

    std::vector<enemy_info> get_wave(int round) {
        std::vector<enemy_info> res = waves[round % waves.size()];
        int add_number = round / waves.size();
        int add_health = add_number * 7;
        for (std::vector<waves::enemy_info>::iterator i = res.begin(); i != res.end(); ++i) {
            i->number += add_number;
            i->health += add_health;
        }
        return res;
    }
}



#endif // WAVES_H_INCLUDED
