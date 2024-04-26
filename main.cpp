#include <iostream>
#include <vector>
#include <fstream>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
#include "Board.h"

using namespace std;

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

    int choice;
    do{
    cout << "Welcome to BugsLife!" << endl;
    cout << "1. Display bugs" << endl;
    cout << "2. Search for a bug" << endl;
    cout << "3. Move all bugs" << endl;
    cout << "4. Display bug paths" << endl;
    cout << "5. Display Cells" << endl;
    cout << "6. Exit" << endl;

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
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice" << endl;
            break;
    }
    }while(choice != 6);

}
