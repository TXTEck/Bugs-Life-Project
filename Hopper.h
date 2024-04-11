#ifndef BUGSLIFE_HOPPER_H
#define BUGSLIFE_HOPPER_H
#include "Bug.h"
#include <cstdlib>

class Hopper : public Bug{
private:
    int hopLength;

public:
    Hopper(int id, pair<int, int> position, int direction, int size, bool alive, int hopLength)
        : Bug(id, std::move(position), direction, size, alive), hopLength(hopLength) {}

    void move() override{
        while(isWayBlocked()){
            direction = (rand() % 4) + 1;
        }
    }
};


#endif //BUGSLIFE_HOPPER_H
