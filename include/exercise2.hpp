#ifndef EXERCISE2_HPP
#define EXERCISE2_HPP

#include <vector>

struct Point {
    double x, y;
    static int angle(Point a, Point b, Point c);
    static double dist(Point a, Point b);
    static std::vector<std::vector<int>> convexHull(std::vector<std::vector<int>> point, int n);
};

#endif