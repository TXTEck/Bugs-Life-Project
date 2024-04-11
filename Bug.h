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
        bool isWayBlocked(){
            int x = position.first;
            int y = position.second;

            switch(direction){
                case 1: //North ↑
                    if(y == 0){
                        return true;
                    }

                case 2: //East →
                    if(x == 9){
                        return true;
                    }

                case 3: //South ↓
                    if(y == 9){
                        return true;
                    }

                case 4: //West ←
                    if(x == 0){
                        return true;
                    }

                default:
                    return false;
            }
        };
};


#endif //BUGSLIFE_BUG_H
