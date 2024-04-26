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
    list<pair<int, int>> path;

public:
    Bug(int id, pair<int, int> position, int direction, int size, bool alive)
            : id(id), position(std::move(position)), direction(direction), size(size), alive(alive) {
        path.push_back(position);
    }



    int getId() const {
        return id;
    }

    void setId(int id) {
        Bug::id = id;
    }

    const pair<int, int> &getPosition() const {
        return position;
    }

    void setPosition(const pair<int, int> &position) {
        Bug::position = position;
    }

    int getDirection() const {
        return direction;
    }

    void setDirection(int direction) {
        Bug::direction = direction;
    }

    int getSize() const {
        return size;
    }

    void setSize(int size) {
        Bug::size = size;
    }

    bool isAlive() const {
        return alive;
    }

    void setAlive(bool alive) {
        Bug::alive = alive;
    }

    const list<pair<int, int>> &getPath() const {
        return path;
    }

    void setPath(const list<pair<int, int>> &path) {
        Bug::path = path;
    }

    virtual void move() = 0;

    bool isWayBlocked() {
        int x = position.first;
        int y = position.second;

        switch (direction) {
            case 1: //North ↑
                if (y == 0) {
                    return true;
                }
                break;
            case 2: //East →
                if (x == 9) {
                    return true;
                }
                break;
            case 3: //South ↓
                if (y == 9) {
                    return true;
                }
                break;
            case 4: //West ←
                if (x == 0) {
                    return true;
                }
                break;
            default:
                break;
        }
        return false;
    };

};


#endif //BUGSLIFE_BUG_H
