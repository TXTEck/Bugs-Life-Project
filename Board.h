
using namespace std;
#ifndef BUGSLIFE_BOARD_H
#define BUGSLIFE_BOARD_H

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
#include "Teleporter.h"


class Board {

private:
    vector<Bug *> bugs_vector;
    const int WIDTH = 10;
    const int HEIGHT = 10;

public:
    void parseLine(const string &strLine) {
        stringstream strStream(strLine);

        const char DELIMITER = ';'; // as this is specified in the specification

        string bug_type;
        getline(strStream, bug_type, DELIMITER);
        string strTemp; // temporary string

        try {
            getline(strStream, strTemp, DELIMITER); // read next field (id) as a string
            int id = stoi(strTemp); // convert string to int conversion (may throw exceptions)

            getline(strStream, strTemp, DELIMITER);
            int x = stoi(strTemp);

            getline(strStream, strTemp, DELIMITER);
            int y = stoi(strTemp);

            pair<int, int> position = make_pair(x, y);

            getline(strStream, strTemp, DELIMITER);
            int direction = stoi(strTemp);

            getline(strStream, strTemp, DELIMITER);
            int size = stoi(strTemp);

            if (bug_type == "C") { // if it is Crawler, then read the Crawler fields
                bugs_vector.push_back(new Crawler(id, position, direction, size, true));
            }
            else if (bug_type == "H") { // if it is Hopper, then read the Hopper fields
                getline(strStream, strTemp, DELIMITER);
                int hopLength = stoi(strTemp);
                bugs_vector.push_back(new Hopper(id, position, direction, size, true, hopLength));
            }
            else if (bug_type == "T")
            {
                bugs_vector.push_back(new Teleporter(id, position, direction, size, true));
            }

        }
        catch (std::invalid_argument const &e) {
            cout;
        }
    }

    void moveBugs() {
        for (int i = 0; i < bugs_vector.size(); i++) {
            if(bugs_vector[i]->isAlive())
                bugs_vector[i]->move();
        }
        checkCell();
        displayBugs();
    }

    void displayBugs() {
        for (int i = 0; i < bugs_vector.size(); i++) {
            int direction = bugs_vector[i]->getDirection();
            string currentDirection, status;
            switch (direction) {
                case 1:
                    currentDirection = "North";
                    break;
                case 2:
                    currentDirection = "East";
                    break;
                case 3:
                    currentDirection = "South";
                    break;
                case 4:
                    currentDirection = "West";
                    break;
            }
            if (bugs_vector[i]->isAlive()) {
                status = "Alive";
            } else {
                status = "Dead";
            }
            if (typeid(*bugs_vector[i]) == typeid(Crawler)) {
                cout
                        << bugs_vector[i]->getId()
                        << " Crawler" <<
                        "  (" << bugs_vector[i]->getPosition().first << " " <<
                        bugs_vector[i]->getPosition().second << ") " <<
                        bugs_vector[i]->getSize() <<
                        "  " << currentDirection <<
                        "  " << status <<
                        endl;
            } else if (typeid(*bugs_vector[i]) == typeid(Hopper)) {
                cout
                        << bugs_vector[i]->getId()
                        << " Hopper" <<
                        "  (" << bugs_vector[i]->getPosition().first << " " <<
                        bugs_vector[i]->getPosition().second << ") " <<
                        bugs_vector[i]->getSize() <<
                        "  " << currentDirection <<
                        "  " << static_cast<Hopper *>(bugs_vector[i])->getHopLength() <<
                        "  " << status <<
                        endl;
            }
            else if (typeid(*bugs_vector[i]) == typeid(Teleporter))
            {
                cout
                        << bugs_vector[i]->getId()
                        << " Teleporter" <<
                        "  (" << bugs_vector[i]->getPosition().first << " " <<
                        bugs_vector[i]->getPosition().second << ") " <<
                        bugs_vector[i]->getSize() <<
                        "  " << currentDirection <<
                        "  " << status <<
                        endl;
            }

        }
    }

    void searchBug(int id) {
        for (int i = 0; i < bugs_vector.size(); i++) {
            if (bugs_vector[i]->getId() == id) {
                cout << "Bug found at position (" << bugs_vector[i]->getPosition().first << " "
                     << bugs_vector[i]->getPosition().second << ")" << endl;
                return;
            }
        }
        cout << "Bug not found" << endl;
    }

    // Range based for loop learnt from https://www.geeksforgeeks.org/range-based-loop-c/
    void displayPath() {
        for (int i = 0; i < bugs_vector.size(); i++) {
            string bugType;
            if (typeid(*bugs_vector[i]) == typeid(Crawler)) {
                bugType = "Crawler";
            } else if (typeid(*bugs_vector[i]) == typeid(Hopper)) {
                bugType = "Hopper";
            } else if (typeid(*bugs_vector[i]) == typeid(Teleporter))
            {
                bugType = "Teleporter";
            }
            cout << bugs_vector[i]->getId() << " " << bugType << " path: ";
            const list<pair<int, int>> &path = bugs_vector[i]->getPath();
            for (auto const &position: path) {
                cout << "(" << position.first << "," << position.second << "), ";
            }

            if (bugs_vector[i]-> isAlive()) {
                cout << "Alive!";
            } else {
                cout << "Eaten by " << bugs_vector[i]->getEatenBy();
            }
            cout << endl;
        }
    };

    void displayCells() {
        for (int i = 0; i < WIDTH; ++i) {
            for (int j = 0; j < HEIGHT; ++j) {
                string cell;
                bool isEmpty = true;

                for (int k = 0; k < bugs_vector.size(); ++k) {
                    if (bugs_vector[k]->getPosition().first == i && bugs_vector[k]->getPosition().second == j) {
                        if (!isEmpty) {
                            cell += ", ";
                        }
                        if (typeid(*bugs_vector[k]) == typeid(Crawler)) {
                            cell += "Crawler " + to_string(bugs_vector[k]->getId());
                        } else if (typeid(*bugs_vector[k]) == typeid(Hopper)) {
                            cell += "Hopper " + to_string(bugs_vector[k]->getId());
                        }
                        else if (typeid(*bugs_vector[k]) == typeid(Teleporter))
                        {
                            cell += "Teleporter " + to_string(bugs_vector[k]->getId());
                        }
                        isEmpty = false;
                    }
                }
                cout << "(" << i << "," << j << "): ";
                if (isEmpty) {
                    cout << "empty" << endl;
                } else {
                    cout << cell << endl;
                }
            }
        }
    }

    vector<Bug *> getBugsVector() const {
        return bugs_vector;
    }

    void checkCell() {
        // Vector to store the bugs in the same cell
        vector<Bug *> bugsInCell;

        for (int i = 0; i < WIDTH; ++i) {
            for (int j = 0; j < HEIGHT; ++j) {
                bugsInCell.clear();  // Clear the vector for new cell

                //Put bugs in the same cell in the vector
                for (int k = 0; k < bugs_vector.size(); ++k) {
                    if (bugs_vector[k]->isAlive() && bugs_vector[k]->getPosition() == make_pair(i, j)) {
                        bugsInCell.push_back(bugs_vector[k]);
                    }
                }

                // If there's more than one bug in the same cell, a fight occurs
                if (bugsInCell.size() > 1) {
                    Bug *winner = fight(bugsInCell);
                    // Process the results of the fight
                    for (Bug *bug: bugsInCell) {
                        if (bug != winner) {
                            winner->grow(bug->getSize());
                            bug->setAlive(false);
                            bug->setEatenBy(winner->getId());
                        }
                    }

                    // Increase the winner's size by the size of the bugs it ate
                    for (Bug *bug: bugsInCell) {
                        if (bug != winner) {
                            winner->grow(bug->getSize());
                        }
                    }
                }
            }
        }
    }

    //Sort function from https://www.geeksforgeeks.org/sorting-a-vector-in-c/
    Bug* fight(vector<Bug *> &bugsInCell) {
        sort(bugsInCell.begin(), bugsInCell.end(), [](Bug *a, Bug *b) {
            return a->getSize() > b->getSize();
        });

        //First bug in the vector is the largest, so assumed to be the winner
        Bug *winner = bugsInCell[0];
        vector<Bug *> sameSizeBugs;
        sameSizeBugs.push_back(winner);

        //Check if there are bugs of the same size
        for (int i = 1; i < bugsInCell.size(); ++i) {
            if (bugsInCell[i]->getSize() == winner->getSize()) {
                sameSizeBugs.push_back(bugsInCell[i]);
            }
        }

        //If there are bugs of the same size, the winner is randomly selected
        if (sameSizeBugs.size() > 1) {
            // Randomly select a bug from the same size bugs
            winner = sameSizeBugs[rand() % sameSizeBugs.size()];
        }

        return winner;
    }

    //Check if there is only one bug alive
    bool simulationEnd()
    {
        int bugsAlive = 0;
        for (int i = 0; i < bugs_vector.size(); i++) {
            if (bugs_vector[i]->isAlive()) {
                bugsAlive++;
                if(bugsAlive > 1)
                {
                    return false;
                }
            }
        }
        return true;
    }

    //Run the simulation each second from https://cplusplus.com/forum/general/101094/#:~:text=just%20pass%20the%20function%20pointer,the%20function%20every%201%20second.
    void runSimulation()
    {
        while(!simulationEnd())
        {
            moveBugs();
            this_thread::sleep_for(chrono::seconds(1));
            cout << "---------------------------------------------------" << endl;
        }
    }
};


#endif //BUGSLIFE_BOARD_H
