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
                if (position.second >= hopLength) { // Check if there's enough space to hop north
                    position.second -= hopLength;
                } else {
                    position.second = 0; // Adjust to boundary if not enough space
                }
                break;
            case 2: // East →
                if (position.first + hopLength <= 9) { // Check if there's enough space to hop east
                    position.first += hopLength;
                } else {
                    position.first = 9; // Adjust to boundary if not enough space
                }
                break;
            case 3: // South ↓
                if (position.second + hopLength <= 9) { // Check if there's enough space to hop south
                    position.second += hopLength;
                } else {
                    position.second = 9; // Adjust to boundary if not enough space
                }
                break;
            case 4: // West ←
                if (position.first >= hopLength) { // Check if there's enough space to hop west
                    position.first -= hopLength;
                } else {
                    position.first = 0; // Adjust to boundary if not enough space
                }
                break;
        }
        path.push_back(position);
    }
};


#endif //BUGSLIFE_HOPPER_H
