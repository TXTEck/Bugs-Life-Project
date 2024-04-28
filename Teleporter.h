//
// Created by System Manager on 28-Apr-24.
//
#ifndef BUGSLIFE_TELEPORTER_H
#define BUGSLIFE_TELEPORTER_H
#include "Bug.h"
#include <cstdlib>

class Teleporter: public Bug{
    private:
        int countTurns = 0;

    public:
        Teleporter(int id, pair<int, int> position, int direction, int size, bool alive)
            : Bug(id, std::move(position), direction, size, alive) {}


        void move() override
        {
            if (isWayBlocked())
            {
                direction = (rand() % 4) + 1;
            }
            switch (direction)
            {
                case 1: // North ↑
                    if (position.second > 0)
                    {
                        position.second--;
                    }
                    else
                    {
                        position.second = 0;
                    }
                    break;
                case 2: // East →
                    if (position.first < 9)
                    {
                        position.first++;
                    }
                    else
                    {
                        position.first = 9;
                    }
                    break;
                case 3: // South ↓
                    if (position.second < 9)
                    {
                        position.second++;
                    }
                    else
                    {
                        position.second = 9;
                    }
                    break;
                case 4: // West ←
                    if (position.first > 0)
                    {
                        position.first--;
                    }
                    else
                    {
                        position.first = 0;
                    }
                    break;
            }
            path.push_back(position);
            countTurns++;
            if(countTurns == 3)
            {
                position.first = rand() % 10;
                position.second = rand() % 10;
                path.push_back(position);
                countTurns = 0;
            }
        }
};


#endif //BUGSLIFE_TELEPORTER_H
