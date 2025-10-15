#include <iostream>
#include <vector>
#include "../include/exercise2.hpp"

using namespace std;

int Point::angle(Point a, Point b, Point c) {
    float area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);

    if(area < 0) return -1; // clockwise

    else if (area > 0) return 1; // counter-clockwise

    return 0;
}

double Point::dist(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

vector<vector<int>> Point::convexHull(vector<vector<int>> points, int n) {
    if (n < 3) return {{-1}}; // convex hull not possible with fewer than 3 points

    vector<Point> a; //converting 2d points into vector of Point type
    for(auto& p : points) {
        a.push_back({(double)p[0], (double)p[1]});
    }


}