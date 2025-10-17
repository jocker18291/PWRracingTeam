#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> //to set the precision
#include "../include/exercise2.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cout << "Usage of: " << argv[0] << " file_name.txt" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Couldn't open the file: " << filename << endl;
        return 1;
    }
}