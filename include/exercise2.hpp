#ifndef EXERCISE2_HPP
#define EXERCISE2_HPP

#include <vector>

struct Point {
    double x, y;
    static int angle(Point a, Point b, Point c);
    static double dist(Point a, Point b);
    static std::vector<std::vector<double>> convexHull(std::vector<std::vector<double>> point, int n);
    static double minWidth(std::vector<std::vector<double>> points, int n);
};

#endif