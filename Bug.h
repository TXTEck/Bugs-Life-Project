#include <utility>
#include <list>
#ifndef BUGSLIFE_BUG_H
#define BUGSLIFE_BUG_H
using namespace std;

class Bug {
protected:
    int id;
    pair<int, int> position;
    int direction;
    int size;
    bool alive;
    list<pair<int,int>> path;

public:
    Bug(int id, pair<int, int> position, int direction, int size, bool alive);

        virtual void move() = 0;

};


#endif //BUGSLIFE_BUG_H
