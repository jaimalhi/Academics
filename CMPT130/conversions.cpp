#include <iostream>
using namespace std;

int main()
{
	//Circle Area
	//Initial variable + pi
	const double pi = 3.14159265359;
	double radius = 0;
	//Visual aspects
	cout << "CIRCLE RADIUS" << endl;
	cout << "-------------" << endl; 
	//User input
	cout << "Enter radius: ";
	cin >> radius;
	cout << endl;
	//Calculations + Message
	double area = pi * (radius*radius);
	cout << "A circle with radius = " << radius << " has an area = " << area << endl;
	cout << endl;

	//Distance
	//Variable + Constants
	double distance = 0;
	const double metersPerFoot = 0.3048;
	const double inchPerFoot = 12.0;
	const double lightspeed = 299792458;
	//Visual aspects
	cout << "DISTANCE" << endl;
	cout << "--------" << endl;
	//User input
	cout << "Enter distance in meters: ";
	cin >> distance;
	cout << endl;
	//Meters to feet and inches
	double feetdecimal = distance / metersPerFoot;
	int feet = feetdecimal;
	double inches = (feetdecimal - feet) * inchPerFoot;
	cout << distance << " meters = " << feet << "' and " << inches << "\"" << endl;
	//Meters to furlongs
	double furlong = distance / 201;
	cout << distance << " meters = " << furlong << " furlongs" << endl;
	//time for light to travel 
	double time = distance / lightspeed;
	cout << "It takes " << time << "s for light to travel " << distance << "m in a vacuum" << endl;

	return 0;
}

