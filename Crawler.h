#ifndef BUGSLIFE_CRAWLER_H
#define BUGSLIFE_CRAWLER_H
#include "Bug.h"
#include <cstdlib>

class Crawler: public Bug{
public:
    Crawler(int id, pair<int, int> position, int direction, int size, bool alive)
        : Bug(id, std::move(position), direction, size, alive) {}

    void move() override{
        bool canMove = false;
        while(!canMove) {
            if (isWayBlocked()) {
                direction = (rand() % 4) + 1;
            } else {
                canMove = true;
            }
        }
        switch(direction){
            case 1: //North ↑
                position.second--;
                break;

            case 2: //East →
                position.first++;
                break;

            case 3: //South ↓
                position.second++;
                break;

            case 4: //West ←
                position.first--;
                break;
        }

        //Record new position in path
        path.push_back(position);
    }
};


#endif //BUGSLIFE_CRAWLER_H
