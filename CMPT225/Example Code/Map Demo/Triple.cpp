/***
 * 
 * Complete your methods for Triple here
 *
 */

#include "Triple.h"
#include <iostream>

using namespace std;


Triple::Triple() : x(0), y(0), z(0) { }


Triple::Triple(double x, double y, double z) : x(x), y(y), z(z) { }


std::ostream& operator<<(std::ostream& os, const Triple v) {
    os << '(' << v.x << ',' << v.y << ',' << v.z << ')';
    return os;
}


Triple& Triple::operator+=(const Triple& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
} // operator+=


