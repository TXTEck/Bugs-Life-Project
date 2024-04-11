#include <utility>
#include <list>
#ifndef BUGSLIFE_BUG_H
#define BUGSLIFE_BUG_H
using namespace std;

class Bug {
protected:
    int id;
    pair<int, int> position;
    int direction; // 1 = North, 2 = East, 3 = South, 4 = West
    int size;
    bool alive;
    list<pair<int,int>> path;

public:
    Bug(int id, pair<int, int> position, int direction, int size, bool alive)
        : id(id), position(std::move(position)), direction(direction), size(size), alive(alive) {}

        virtual void move() = 0;
        bool isWayBlocked();{
            int x = position.first;
            int y = position.second;

            switch(direction){
                case 1:
                    return y == 0;
                case 2:
                    return x ==9;
                case 3:
                    return y == 9;
                case 4:
                    return x == 0;
                default
                    return false;
            }
        };
};


#endif //BUGSLIFE_BUG_H
