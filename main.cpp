#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "Bug.h"
#include "Board.h"
#include "ctime"

using namespace std;
using namespace sf;
void writeToFile(const vector<Bug*>& bugs_vector);
int main() {

    Board board;
    ifstream file("bugs.txt");

    if(file) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                board.parseLine(line);
            }
        }
    } else {
        cout << "Unable to open file" << endl;
    }
    file.close();
    cout << "Welcome to BugsLife!" << endl;
    int choice;
    do{
    cout << "1. Display bugs" << endl;
    cout << "2. Search for a bug" << endl;
    cout << "3. Move all bugs" << endl;
    cout << "4. Display bug History" << endl;
    cout << "5. Display Cells" << endl;
    cout << "6. Run Simulation" << endl;
    cout << "7. Exit" << endl;

    cin >> choice;
    switch (choice) {
        case 1:
            board.displayBugs();
            break;
        case 2:
            cout << "Enter bug ID: ";
            int id;
            cin >> id;
            board.searchBug(id);
            break;
        case 3:
            board.moveBugs();
            break;
        case 4:
            board.displayPath();
            break;
        case 5:
            board.displayCells();
            break;
        case 6:
            board.runSimulation();
            writeToFile(board.getBugsVector());
            break;
        case 7:
            writeToFile(board.getBugsVector());
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice" << endl;
            break;
        }

    }while(choice != 7);

}

//How to format time from https://en.cppreference.com/w/cpp/io/manip/put_time
void writeToFile(const vector<Bug*>& bugs_vector)
{
    time_t t = time(0);
    tm tm = *localtime(&t);
    stringstream ss;
    ss << put_time(&tm, "%Y-%m-%d_%H-%M-%S");
    string filename = "bugs_life_history_" + ss.str() + ".out";

    ofstream fout(filename);
    if(fout)
    {
        for (int i = 0; i < bugs_vector.size(); i++) {
            string bugType;
            if (typeid(*bugs_vector[i]) == typeid(Crawler)) {
                bugType = "Crawler";
            } else if (typeid(*bugs_vector[i]) == typeid(Hopper)) {
                bugType = "Hopper";
            }
            else if (typeid(*bugs_vector[i]) == typeid(Teleporter)) {
                bugType = "Teleporter";
            }
            fout << bugs_vector[i]->getId() << " " << bugType << " path: ";
            const list<pair<int, int>>& path = bugs_vector[i]->getPath();
            for (auto const& position : path) {
                fout << "(" << position.first << "," << position.second << "), ";
            }
            if (bugs_vector[i]-> isAlive()) {
                fout << "Alive!";
            } else {
                fout << "Eaten by " << bugs_vector[i]->getEatenBy();
            }
            fout << endl;
        }
        fout.close();
    }
    else{
        cout << "Unable to open file" << endl;
    }
}

