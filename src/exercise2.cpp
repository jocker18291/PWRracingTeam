#include <iostream>
#include "../include/exercise2.hpp"

using namespace std;

int Point::angle(Point a, Point b, Point c) {
    float area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);

    if(area < 0) return -1; // clockwise

    else if (area > 0) return 1; // counter-clockwise

    return 0;
}