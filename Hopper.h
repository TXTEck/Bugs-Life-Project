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

    int getHopLength() const {
        return hopLength;
    }
        void move() override{

        while(isWayBlocked()){
            direction = rand() % 4 + 1;
        }
        switch (direction) {
            case 1: // North ↑
                if (position.second >= hopLength) {
                    position.second -= hopLength;
                } else {
                    position.second = 0;
                }
                break;
            case 2: // East →
                if (position.first + hopLength <= 9) {
                    position.first += hopLength;
                } else {
                    position.first = 9;
                }
                break;
            case 3: // South ↓
                if (position.second + hopLength <= 9) {
                    position.second += hopLength;
                } else {
                    position.second = 9;
                }
                break;
            case 4: // West ←
                if (position.first >= hopLength) {
                    position.first -= hopLength;
                } else {
                    position.first = 0;
                }
                break;
        }
        path.push_back(position);
    }
};


#endif //BUGSLIFE_HOPPER_H
