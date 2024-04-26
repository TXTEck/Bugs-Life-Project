
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
    }
};


#endif //BUGSLIFE_BOARD_H
