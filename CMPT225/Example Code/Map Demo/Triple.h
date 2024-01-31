/***
 * 
 * interface for Triple
 *
 */

#include <iostream>


class Triple {
    public:
        Triple();
        Triple(double x, double y, double z);

        friend std::ostream& operator<<(std::ostream& os, const Triple v);

        double getX() const { return x; }
        double getY() const { return y; }
        double getZ() const { return z; }

        Triple& operator+=(const Triple& rhs);
        bool operator<(const Triple& rhs) const {
            return x < rhs.x || x == rhs.x && y < rhs.y || x == rhs.x && y == rhs.y && z < rhs.z;
        }

    private:
        double x;
        double y;
        double z;
};


class TripleLess {
    public:

        bool operator()( const Triple& lhs, const Triple& rhs) const {
            // return lhs.getX() < rhs.getX(); // if you do this, then two Triples will be lost
            return lhs.getX() < rhs.getX() || lhs.getX() == rhs.getX() && lhs.getY() < rhs.getY() || lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY() && lhs.getZ() < rhs.getZ();
        }
    
};



