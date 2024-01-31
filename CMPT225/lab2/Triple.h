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

        friend void print(const Triple v);
        friend double dotProduct(const Triple v, const Triple w);
		friend std::ostream& operator<<(std::ostream& os, const Triple v);


        //  You will implement the following in Lab 2
        double operator*(const Triple& rhs) const;
        Triple operator+(const Triple& rhs) const;
        Triple& operator+=(const Triple& rhs);

    private:
        double x;
        double y;
        double z;
};



