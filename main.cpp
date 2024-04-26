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
    ifstream file("bugs.txt"); // Ensure this is the correct path to your file

    if(file) {
        string line;
        while (getline(file, line)) {  // This reads an entire line until a newline character
            if (!line.empty()) {
                board.parseLine(line);
            }
        }
        file.close();  // Close the file when you're done reading
    } else {
        cout << "Unable to open file" << endl;
    }

    board.displayBugs();
    return 0;
}
