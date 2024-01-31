//Lab 10
#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.14159;

// Circle struct goes here
struct Circle {
    int x;
    int y;
    double radius;
};

// Function prototypes
bool intersect(const Circle& c1, const Circle& c2);
double area(const Circle& c);

int main()
{
       Circle c1 = { 5, 6, 3.2 };
       Circle c2 = { 6, 8, 1.2 };

       // Intersect test 1
       if (intersect(c1, c2)) {
              cout << "The circles intersect" << endl;
       }
       else {
              cout << "The circles do NOT intersect" << endl;
       }

       // Intersect test 2
       Circle c3 = { 12, 2, 3.2 };
       Circle c4 = { 2, 12, 5.7 };

       if (intersect(c3, c4)) {
              cout << "The circles intersect" << endl;;
       }
       else {
              cout << "The circles do NOT intersect" << endl;
       }

       // Area test
       cout << endl << "Area of c1 = " << area(c1) << endl << endl;

       return 0;
}

bool intersect(const Circle& c1, const Circle& c2){
    int xDiff = pow((c1.x - c2.x),2);
    int yDiff = pow((c1.y - c2.y),2);
    double sumOfRad = c1.radius + c2.radius;
    double distance = sqrt(xDiff + yDiff);

    if(sumOfRad > distance){
        return true;
    }
    else{
        return false;
    }
}

double area(const Circle& c){
    double cArea = PI * pow(c.radius,2);

    return cArea;
}
