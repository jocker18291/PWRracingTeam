#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/exercise2.hpp"

using namespace std;

int Point::angle(Point a, Point b, Point c) { //method that calculates the orientation between points
    float area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);

    if(area < 0) return -1; // clockwise

    else if (area > 0) return 1; // counter-clockwise

    return 0;
}

double Point::dist(Point a, Point b) { //calculating the square of a distance
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

vector<vector<double>> Point::convexHull(vector<vector<double>> points, int n) {
    if (n < 3) return {{-1}}; // convex hull not possible with fewer than 3 points

    vector<Point> a; //converting 2d points into vector of Point type
    for(auto& p : points) {
        a.push_back({(double)p[0], (double)p[1]});
    }

    Point p0 = *min_element(a.begin(), a.end(), [](Point a, Point b) { //looking for the 'lowest' starting point, if there is a double - choose the one on the most left
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });

    sort(a.begin(), a.end(), [&p0](Point a, Point b) { // sorting the vector based on polar angle
        int o = Point::angle(p0, a, b);
        if(o ==0) { //if two points are collinear -> keep farther one last
            return Point::dist(p0, a) < Point::dist(p0, b);
        }
        return o < 0; //sort counter-clockwise
    });

    vector<Point> hull; //creating vector to store the convex hull
    for(auto& cur : a) { // iterating through all points
        while (hull.size() > 1 && angle(hull[hull.size() - 2], hull.back(), cur) >= 0) { //if there is a point where it is not a left turn -> pop the middle element
            hull.pop_back();
        }
        hull.push_back(cur); //add the current point to the convex hull
    }

    if(hull.size() < 3) return {{-1}}; // there cannot be a convex hull with fewer than 3 elements

    vector<vector<double>> res;
    for(auto& it : hull) //creating vector as a result to return
        res.push_back({(double)it.x, (double)it.y});
    
    return res;
}

double Point::minWidth(vector<vector<double>> points, int n) {
    if(n < 3) return 0.0;

    auto hull = convexHull(points, n); // here we find a convex hull
    int m = hull.size();
    if (m < 3) return 0.0;

    vector<Point> poly; //now we convert every point to Point variable in a vector
    for(auto& p : hull) poly.push_back({p[0], p[1]});

    double minWidth = 1e18; //we set a very large number
}