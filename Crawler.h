#ifndef BUGSLIFE_CRAWLER_H
#define BUGSLIFE_CRAWLER_H
#include "Bug.h"
#include <cstdlib>

class Crawler: public Bug{
public:
    Crawler(int id, pair<int, int> position, int direction, int size, bool alive)
        : Bug(id, std::move(position), direction, size, alive) {}

    void move() override{
        while(isWayBlocked()){
            direction = (rand() % 4) + 1;
        }
    }
};


#endif //BUGSLIFE_CRAWLER_H
