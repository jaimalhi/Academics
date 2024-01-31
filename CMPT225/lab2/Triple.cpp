/***
 * 
 * Complete your methods for Triple here
 *
 */

#include "Triple.h"
#include <iostream>
using namespace std;


Triple::Triple() : x(0), y(0), z(0) { };


Triple::Triple(double x, double y, double z) : x(x), y(y), z(z) { };


std::ostream& operator<<(std::ostream& os, const Triple v) {
    os << '(' << v.x << ',' << v.y << ',' << v.z << ')';
    return os;
}

void print(const Triple v) {
    cout << '(' << v.x << ',' << v.y << ',' << v.z << ')';
} // print


double dotProduct(const Triple v, const Triple w) {
    double ret = 0.0;

    ret += v.x * w.x;
    ret += v.y * w.y;
    ret += v.z * w.z;

    return ret;
} // dotProduct


double Triple::operator*(const Triple& rhs) const {
    double ret = 0.0;
    //(*this) = this->
    ret += this->x * rhs.x;
    ret += this->y * rhs.y;
    ret += this->z * rhs.z;

    return ret;
} // operator*


Triple Triple::operator+(const Triple& rhs) const {
    // this->x + rhs.x;
    // this->y + rhs.y;
    // this->z + rhs.z;

    return Triple();
} // operator+


Triple& Triple::operator+=(const Triple& rhs) {
    this->x = this->x + rhs.x;
    this->y = this->y + rhs.y;
    this->z = this->z + rhs.z;

    return *this;
} // operator+=


