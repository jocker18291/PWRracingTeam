#ifndef EXERCISE2_HPP
#define EXERCISE2_HPP

#include <vector>

struct Point {
    double x, y;
    int angle(Point a, Point b, Point c);
    double dist(Point a, Point b);
};

#endif