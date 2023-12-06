#include <iostream>
#include <cmath>
using namespace std;

enum Region {
    REGION_1 = 1,
    REGION_2,
    REGION_3,
    REGION_4,
    REGION_5,
    REGION_6,
    REGION_7,
    REGION_8,
    ORIGIN,
    OTHER
};

struct Point {
    float x, y, z;

    // Constructor
    Point(float x_val, float y_val, float z_val) : x(x_val), y(y_val), z(z_val) {}

    // Function to calculate the distance to the origin (0, 0, 0)
    float zero_distance() {
        return sqrt(x * x + y * y + z * z);
    }

    // Function to calculate the distance between two points
    float distance(Point other) {
        float dx = x - other.x;
        float dy = y - other.y;
        float dz = z - other.z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }

    // Function to compare two points and return the one further from the origin
    Point compare(Point other) {
        if (this->zero_distance() > other.zero_distance()) {
            return *this;
        } else {
            return other;
        }
    }

    // Function to determine the region of the point in 3D space
    Region region() {
        if (x == 0 && y == 0 && z == 0) {
            return ORIGIN;
        } else if (x > 0) {
            if (y > 0) {
                if (z > 0) {
                    return REGION_1;
                } else if (z < 0) {
                    return REGION_2;
                }
            } else if (y < 0) {
                if (z > 0) {
                    return REGION_5;
                } else if (z < 0) {
                    return REGION_6;
                }
            }
        } else if (x < 0) {
            if (y > 0) {
                if (z > 0) {
                    return REGION_4;
                } else if (z < 0) {
                    return REGION_3;
                }
            } else if (y < 0) {
                if (z > 0) {
                    return REGION_8;
                } else if (z < 0) {
                    return REGION_7;
                }
            }
        }
        return OTHER;
    }


    // Function to check if two points are in the same region
    bool is_in_same_region(Point other) {
        return this->region() == other.region();
    }
};
int main(){
    // Create Point objects
    Point p1(3, 4, 5);
    Point p2(9, -8, 3);

    // Call the zero_distance function on the Point object
    float distance = p1.zero_distance();

    // Call the distance function to calculate the distance between two points
    float between_distance = p1.distance(p2);

    // Call the compare function to get the point further from the origin
    Point compared_point = p1.compare(p2);

    // Call the region function to get the region of the point
    Region point_region = p2.region();

    // Print the results
    cout << "Distance to the origin: " << distance << endl;
    cout << "Distance between two points: " << between_distance << endl;
    cout << "Point further from the origin: (" << compared_point.x << ", " << compared_point.y << ", " << compared_point.z << ")" << endl;
    
    return 0;
}

