/*
	SBTU - Module Project
	Semester 1
	Computer Engineering
	Tuna Figankaplan, Ali Bozkurt, Sude Yildirim, Burak Yalituna
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

// Declaring variables
const float GRAVITY = 9.8;
const float PI = 3.14159;
float initialSpeed, angle, height, ftime, _distance;
float radian;

// Function that returns the bigger root of a quadratic equation. Format: ax^2 + bx + c = 0 
float solveForQuadraticEquation(float a, float b, float c) {
	if (a == 0) {
		throw new exception("This is not a quadratic equation!");
	}

	float delta = pow(b, 2) - 4 * a * c;

	if (delta < 0) {
		throw new exception("There is no real solution for this quadratic equation!");
	}
	else {
		return (- b + sqrt(delta)) / (2 * a);
	}
}

// Returns the flight time by solving the quadratic equation 
float findTheFlightTime() {
	float a = GRAVITY / 2;
	float b = initialSpeed * sin(radian);
	float c = -height;
	return solveForQuadraticEquation(a, b, c);
}

vector<float> positionVectorOverTime(float t) {
	vector<float> component = { initialSpeed * cos(radian) * t, (-initialSpeed * sin(radian) * t) + (-GRAVITY / 2 * t * t) };
	return component;
}

int main()
{
	cout << "Please enter the initial speed of the snowball (m/s): ";
	cin >> initialSpeed;

	cout << "Please enter the slope angle of the roof (degree): ";
	cin >> angle;
	radian = angle * PI / 180;

	cout << "Please enter the height (m): ";
	cin >> height;

	ftime = findTheFlightTime();
	_distance = (initialSpeed * cos(radian)) * ftime;

	cout << "------------------------------------------------------------------------------------------------------" << endl;
	cout << "1) Display the time of flight.\n2) Find the impact point.\n3) Horizontal and vertical coordinates of the snowball's motion over time.\n4) Decide if the snowball will hit the person or not.\n5) Exact distance at which the snowball will hit a person standing at a specified distance and height.\n9) Exit\nHello, please choose the option that you want to perform. Enter '9' to exit the program." << endl;
	cout << "------------------------------------------------------------------------------------------------------\n" << endl;

	while (true) {
		char option;
		
		cin >> option;

		switch (option)
		{
			case '1': // Flight time
				cout << fixed << setprecision(3) << "Flight time is " << ftime << " seconds.\n" << endl;
				break;
			case '2': // Impact point
				cout << fixed << setprecision(3) << "The ball will hit the ground " << _distance << " meters away from the edge of the barn.\n" << endl;
				break;
			case '3': // 
				cout << ftime * 0.25 << " seconds: R = (" << positionVectorOverTime(ftime * 0.25)[0] << " i " << positionVectorOverTime(ftime * 0.25)[1] << " j) m" << endl;
				cout << ftime * 0.5 << " seconds: R = (" << positionVectorOverTime(ftime * 0.5)[0] << " i " << positionVectorOverTime(ftime * 0.5)[1] << " j) m" << endl;
				cout << ftime * 0.75 << " seconds: R = (" << positionVectorOverTime(ftime * 0.75)[0] << " i " << positionVectorOverTime(ftime * 0.75)[1] << " j) m" << endl;
				cout << ftime << " seconds: R = (" << positionVectorOverTime(ftime)[0] << " i " << positionVectorOverTime(ftime)[1] << " j) m" << endl;
				cout << endl;
				break;
			case '4': // 
				cout << "\n" << endl;
				break;
			case '5': // 
				cout << "\n" << endl;
				break;
			case '9': //
				cout << "Closing the program...\n" << endl;
				return 0;
			default:
				cout << "Invalid operation please try again.\n" << endl;
				break;
		}
    }
}