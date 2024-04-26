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
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }

    board.displayBugs();
    return 0;
}
