
using namespace std;
#ifndef BUGSLIFE_BOARD_H
#define BUGSLIFE_BOARD_H
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"


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
            if (bug_type == "C") { // if it is Crawler, then read the Crawler fields
                getline(strStream, strTemp, DELIMITER); // read next field (id) as a string
                int id = stoi(strTemp); // convert string to int conversion (may throw exceptions)

                getline(strStream, strTemp, DELIMITER);
                int x = stoi(strTemp);

                getline(strStream, strTemp, DELIMITER);
                int y = stoi(strTemp);

                pair <int, int> position = make_pair(x, y);

                getline(strStream, strTemp, DELIMITER);
                int direction = stoi(strTemp);

                getline(strStream, strTemp, DELIMITER);
                int size = stoi(strTemp);


                bugs_vector.push_back(new Crawler(id, position, direction, size, true));


            } else if (bug_type == "H") { // if it is Hopper, then read the Hopper fields
                getline(strStream, strTemp, DELIMITER); // read next field (id) as a string
                int id = stoi(strTemp); // convert string to int conversion (may throw exceptions)

                getline(strStream, strTemp, DELIMITER); // read next field (id) as a string
                int x = stoi(strTemp); // convert string to int conversion (may throw exceptions)

                getline(strStream, strTemp, DELIMITER);
                int y = stoi(strTemp);

                pair <int, int> position = make_pair(x, y);

                getline(strStream, strTemp, DELIMITER);
                int direction = stoi(strTemp);

                getline(strStream, strTemp, DELIMITER);
                int size = stoi(strTemp);

                getline(strStream, strTemp, DELIMITER);
                int hopLength = stoi(strTemp);



                bugs_vector.push_back(new Hopper(id, position, direction, size, true, hopLength));
            }

        }
        catch (std::invalid_argument const &e) {
            cout;
        }
    }

    void moveBugs(){
        for(int i = 0; i < bugs_vector.size(); i++){
            bugs_vector[i]->move();
        }

        displayBugs();
    }

    void displayBugs(){
        for(int i = 0; i < bugs_vector.size(); i++){
            int direction = bugs_vector[i]->getDirection();
            string currentDirection,status;
            switch(direction){
                case 1:
                    currentDirection = "North";
                    break;
                case 2:
                    currentDirection =  "East";
                    break;
                case 3:
                    currentDirection =  "South";
                    break;
                case 4:
                    currentDirection =  "West";
                    break;
            }
            if(bugs_vector[i]->isAlive()){
                status = "Alive";}
            else{
                status = "Dead";
            }
            if(typeid(*bugs_vector[i]) == typeid(Crawler)){
                cout
                << bugs_vector[i]->getId()
                << " Crawler" <<
                "  (" << bugs_vector[i]->getPosition().first << " " <<
                bugs_vector[i]->getPosition().second << ") " <<
                bugs_vector[i]->getSize() <<
                "  " << currentDirection <<
                "  " << status <<
                endl;
            }
            else if(typeid(*bugs_vector[i]) == typeid(Hopper))
            {
                cout
                << bugs_vector[i]->getId()
                << " Hopper" <<
                "  (" << bugs_vector[i]->getPosition().first << " " <<
                bugs_vector[i]->getPosition().second << ") " <<
                bugs_vector[i]->getSize() <<
                "  " << currentDirection <<
                "  " << static_cast<Hopper*>(bugs_vector[i])->getHopLength() <<
                "  " << status <<
                endl;
            }

        }
    }

    void searchBug(int id){
        for(int i = 0; i < bugs_vector.size(); i++){
            if(bugs_vector[i]->getId() == id){
                cout << "Bug found at position (" << bugs_vector[i]->getPosition().first << " " << bugs_vector[i]->getPosition().second << ")" << endl;
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
            }
            cout << "Bug " << bugs_vector[i]->getId() << " " << bugType << " path: ";
            const list<pair<int, int>>& path = bugs_vector[i]->getPath();
            for (auto const& position : path) {
                cout << "(" << position.first << " " << position.second << ") ";
            }
            cout << endl;
        }
    };

    void displayCells()
    {
        for (int i = 0; i < WIDTH; ++i) {
            for (int j = 0; j < HEIGHT; ++j) {
                string cell;
                bool isEmpty = true;

                for (int k = 0; k < bugs_vector.size(); ++k) {
                    if (bugs_vector[k]->getPosition().first == i && bugs_vector[k]->getPosition().second == j) {
                        if (!isEmpty) {
                            cell += ", ";
                        }
                        if(typeid(*bugs_vector[k]) == typeid(Crawler)){
                            cell += "Crawler " + to_string(bugs_vector[k]->getId());
                        }
                        else if(typeid(*bugs_vector[k]) == typeid(Hopper)){
                            cell += "Hopper " + to_string(bugs_vector[k]->getId());
                        }
                        isEmpty = false;
                    }
                }
                cout << "(" << i << "," << j << "): ";
                if (isEmpty)
                {
                    cout << "empty" << endl;
                }
                else
                {
                    cout << cell << endl;
                }
            }
        }
    }
};


#endif //BUGSLIFE_BOARD_H
