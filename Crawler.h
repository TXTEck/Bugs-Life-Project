#ifndef BUGSLIFE_CRAWLER_H
#define BUGSLIFE_CRAWLER_H

#include "Bug.h"
#include <cstdlib>

class Crawler : public Bug {
public:
    Crawler(int id, pair<int, int> position, int direction, int size, bool alive)
            : Bug(id, std::move(position), direction, size, alive) {}

    void move() override {
        if (isWayBlocked()) {
            direction = (rand() % 4) + 1;
        }
        switch (direction) {
            case 1: // North ↑
                if (position.second > 0) {
                    position.second--;
                } else {
                    position.second = 0;
                }
                break;
            case 2: // East →
                if (position.first < 9) {
                    position.first++;
                } else {
                    position.first = 9;
                }
                break;
            case 3: // South ↓
                if (position.second < 9) {
                    position.second++;
                } else {
                    position.second = 9;
                }
                break;
            case 4: // West ←
                if (position.first > 0) {
                    position.first--;
                } else {
                    position.first = 0;
                }
                break;

        }

        //Record new position in path
        path.push_back(position);
    }
};


#endif //BUGSLIFE_CRAWLER_H
