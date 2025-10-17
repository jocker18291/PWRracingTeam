# Convex Hull, Minimal Width & Closest Pair Algorithms

## Description

This solution implements three advanced geometric algorithms:
1. **Convex Hull** - Algorithm for calculating the convex hull (the smallest convex polygon that contains all points).
2. **Closest Parallel Lines** - Calculating the closest pair of parallel lines that enclose all points.
3. **Closest Pair** - Finding the two closest points in a set of points.

## Technologies Used
- **C++11**: Modern C++ features, including lambdas and `std::function`.
- **Geometric Algorithms:**
  - **Convex Hull Algorithm**: Implementation of the "Graham Scan" (or variant) algorithm to find the points forming the convex hull.
  - **Closest Parallel Lines**: Using the **rotating calipers** method to calculate the minimal distance between two parallel lines.
  - **Closest Pair**: Implementation of the "Divide and Conquer" algorithm to find the closest pair of points in the set.
 
## How it Works
1. **Convex Hull**
The `convexHull()` function finds the set of points that form the convex hull for a given set of 2D points. The algorithm works as follows:
- First, it identifies the lowest (or leftmost) point.
- Then, the points are sorted by polar angle relative to this point.
- A stack is used to keep track of the points that are part of the convex hull. If the next point would cause a clockwise turn, it is discarded.

The final result is a set of points that defines the convex polygon surrounding all the given points.

2. **Closest Parallel Lines**
The `minWidth()` function calculates the minimal distance between two **parallel lines** that enclose all the points.
- The algorithm first finds the convex hull of the points.
- Using **rotating calipers**, it calculates the minimal distance between two parallel lines that bound the points in the convex hull.

4. **Closest Pair**
The `closestPair()` function uses the **Divide and Conquer** approach to find the two closest points in a set of points. The algorithm works by:
- Sorting the points based on their x-coordinates.
- Recursively dividing the points into two halves and finding the closest pair in each half.
- Then, the algorithm checks the "strip" of points near the dividing line to ensure that no closer pair exists between the two halves.

## Key Functions:
- `angle()`: Calculates the orientation (clockwise, counter-clockwise, or collinear) of three points.
- `dist()`: Calculates the squared Euclidean distance between two points.
- `convexHull()`: Finds the convex hull of a set of points.
- `minWidth()`: Computes the minimal distance between the closest pair of parallel lines that enclose the points.
- `closestPair()`: Finds the closest pair of points in the set using divide and conquer.
- `findClosestPair()`: Converts input points to a `Point` struct and calls `closestPair()`.


## Edge Cases and Considerations
1. **Convex Hull**
   - **Edge Case**: If there are fewer than 3 points, no convex hull can be formed. The function will return `{-1}` in such cases.
   - **Performance**: The time complexity of the convex hull algorithm is \(O(n log n)\), which is efficient enough for most practical input sizes.
2. **Closest Parallel Lines**
   - **Edge Case**: If the number of points is less than 3, the minimal distance between parallel lines cannot be calculated. The function will return `0.0` in such cases.
   - **Performance**: The algorithm uses rotating calipers, which runs in linear time after calculating the convex hull, making it efficient with \(O(n)\) complexity after hull computation.
3. **Closest Pair**
   - **Edge Case**: If there are fewer than 2 points, there is no valid closest pair. The function will return `0.0` in such cases.
   - **Performance**: The divide and conquer approach has a time complexity of \(O(n log n)\), which is much more efficient than the brute force \(O(n^2)\) approach.
