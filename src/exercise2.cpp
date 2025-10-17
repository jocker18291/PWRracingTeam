#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>
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
    //rotating calipers
    for (int i = 0, j = 1; i < m; i++) {
        int ni = (i + 1) % m; // next point
        //side vector
        double dx = poly[ni].x - poly[i].x;
        double dy = poly[ni].y - poly[i].y;
        double len = sqrt(dx*dx + dy*dy);

        while(fabs((poly[(j+1) % m].x - poly[i].x) * dy - (poly[(j+1) % m].y - poly[i].y)*dx) > fabs((poly[j].x - poly[i].x) * dy - (poly[j].y - poly[i].y) * dx)) {
            j = (j + 1) % m;
        } // move j until the distance to the next point decreases

        double distance = fabs((poly[j].x - poly[i].x) * dy - (poly[j].y - poly[i].y) * dx) / len;
        minWidth = min(minWidth, distance);
    };

    return minWidth;
}

double Point::closestPair(vector<Point>& points, int n) {
    if(n < 2) return 0.0; //there is no closest pair without a pair

    sort(points.begin(), points.end(), [](Point a, Point b) { return a.x < b.x;}); // sort by x coordinate

    auto distance = [](Point a, Point b) { //calculate the distance between two points
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    };

    function<double(int, int)> closest = [&](int left, int right){ //helper function for divide and conquer algorithm
        if (right - left <= 3) { //when there are up to three points in a strip we calculate the distance between them all
            double minDist = numeric_limits<double>::infinity();
            for(int i = left; i < right; ++i) {
                for(int j = i + 1; j < right; ++j) {
                    minDist = min(minDist, distance(points[i], points[j]));
                }
            }
            return minDist;
        }

        int mid = (left + right) / 2;
        double midX = points[mid].x;
        double leftDist = closest(left, mid); //recurence to make strips
        double rightDist = closest(mid, right); //recurence to make strips

        double minDist = min(leftDist, rightDist);

        vector<Point> strip; //create the strip of points that are closer or equal to minDist
        for(int i = left; i < right; ++i) {
            if (abs(points[i].x - midX) < minDist) {
                strip.push_back(points[i]);
            }
        }

        for (int i = 0; i < strip.size(); ++i) { //amongst those points we calculate the minDist
            for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
                minDist = min(minDist, distance(strip[i], strip[j]));
            }
        }

        return minDist;
    };

    return closest(0, n);
}

vector<vector<double>> Point::findClosestPair(vector<vector<double>>& points, int n) {
    vector<Point> pointList;
    for(auto& p : points) { //converting vector of a vector to a vector of Point type
        pointList.push_back({p[0], p[1]});
    }

    double closestDist = closestPair(pointList, n);
    vector<vector<double>> result;
    for(int i  = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            if(sqrt(dist(pointList[i], pointList[j])) == closestDist) {
                result.push_back({pointList[i].x, pointList[i].y});
                result.push_back({pointList[j].x, pointList[j].y});
                return result;
            }
        }
    }
    return result;
}