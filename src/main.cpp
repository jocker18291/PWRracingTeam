#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> //to set the precision
#include <cmath>
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

    int n;
    file >> n; //we read the first line
    vector<vector<double>> points(n, vector<double>(2)); //we create a vector of size n x 2

    for(int i = 0; i < n; i++) {
        file >> points[i][0] >> points[i][1];
    }
    file.close();

    //Convex Hull
    auto hull = Point::convexHull(points, n);
    cout << "Convex Hull: ";
    for(auto& p : hull) {
        cout << "(" << p[0] << ", " << p[1] << ") ";
    }
    cout << endl;

    //minimal width
    double width = Point::minWidth(points, n);
    cout << fixed << setprecision(4);
    cout << "Lines: d=" << width << endl;

    //closest pair
    auto closestPoints = Point::findClosestPair(points, n);
    double closestDist = sqrt(Point::dist({closestPoints[0][0], closestPoints[0][1]}, {closestPoints[1][0], closestPoints[1][1]}));
    cout << "Closest Points: (" << closestPoints[0][0] << ", " << closestPoints[0][1] << "), ";
    cout << "(" << closestPoints[1][0] << ", " << closestPoints[1][1] << ") d=" << fixed << setprecision(4) << closestDist << endl;
}