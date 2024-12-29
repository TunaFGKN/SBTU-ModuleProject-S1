/*
	SBTU - Computer Engineering
	Module Project - Semester 1
	Tuna Figankaplan, Ali Bozkurt, Sude Yildirim, Burak Yalituna
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include "gnuplot-iostream.h"

using namespace std;

const float GRAVITY = 9.8;
const float PI = 3.14159;
float initialSpeed, angle, height;
float radian, ftime, impactPoint;

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

float findTheFlightTime() {
	return solveForQuadraticEquation(GRAVITY/2, initialSpeed * sin(radian), -height);
}

// Returns the x and y components of the position vector at an exact time as a vector.
vector<float> positionVectorOverTime(float t) {
	vector<float> component = {initialSpeed * cos(radian) * t, (initialSpeed * sin(radian) * t) + (GRAVITY / 2 * t * t)};
	return component;
}

void printPosition(float timeFraction = 1) {
	cout << ftime * timeFraction << " seconds: R = (" << positionVectorOverTime(ftime * timeFraction)[0] << "i - " << positionVectorOverTime(ftime * timeFraction)[1] << "j) m" << endl;
}

void plotTrajectory() {
	cout << "Calculating the trajectory...\n" << endl;	
	Gnuplot gp("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persist");

	vector<pair<float, float>> trajectoryData; 

	for (float t = 0; t <= ftime; t += 0.01) {
		float x = initialSpeed * cos(radian) * t;
		float y = (-initialSpeed * sin(radian) * t) - (0.5 * GRAVITY * t * t);

		if (x == impactPoint) break; // Stop when it touches the ground

		trajectoryData.push_back(make_pair(x, y)); // Data
	}

	// GNUPlot commands
	gp << "set title 'Projectile Motion Trajectory'\n";
	gp << "set xlabel 'Horizontal Distance (m)'\n";
	gp << "set ylabel 'Vertical Distance (m)'\n";
	gp << "plot '-' with lines title 'Trajectory'\n";

	// Send data to gnuplot
	gp.send1d(trajectoryData);
}

float calculateDistanceToHitThePerson() {
	return initialSpeed * cos(radian) * solveForQuadraticEquation(GRAVITY / 2, initialSpeed * sin(radian), -height + 1.9);
}

bool validationCheck(float initialSpeed, float angle, float height) {
	if (initialSpeed <= 0) return 0;
	if ((angle > 90) && (angle <= 0)) return 0;	
	if (height <= 0) return 0;
	return 1;
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

	if (!validationCheck(initialSpeed, angle, height)) {
		cout << endl << "Invalid inputs. Please try again." << endl;
		return 0;
	}

	ftime = findTheFlightTime();
	impactPoint = initialSpeed * cos(radian) * ftime;
	
	cout << fixed << setprecision(3);
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	cout << "1) Display the time of flight.\n2) Find the impact point.\n3) Horizontal and vertical coordinates of the snowball's motion over time.\n4) Decide if the snowball will hit the person or not.\n5) Exact distance at which the snowball will hit a person standing at a specified distance and height.\n6) Plot the trajectory.\n9) Exit\nHello, please choose the option that you want to perform. Enter '9' to exit the program." << endl;
	cout << "------------------------------------------------------------------------------------------------------\n" << endl;

	while (true) {
		int option;
		cout << "Please enter the option that you want to perform: ";
		cin >> option;

		switch (option)
		{
			case 0:
				cout << "Returning to the beginning...\n" << endl;
				main();
				return 0;
			case 1:
				cout << "Flight time is " << ftime << " seconds.\n" << endl;
				break;
			case 2: 
				cout << "The ball will hit the ground " << impactPoint << " meters away from the edge of the barn.\n" << endl;
				break;
			case 3: 
				printPosition(0.25);
				printPosition(0.5);
				printPosition(0.75);
				printPosition(1);
				cout << endl;
				break;
			case 4: 
				if (impactPoint < 4) {
					cout << "Snowball will not hit the person.\n" << endl;
					break;
				}
				if (calculateDistanceToHitThePerson() < 4) {
					cout << "\aSnowball will hit the person.\n" << endl;
				}
				else {
					cout << "Snowball will not hit the person.\n" << endl;
				}
				break;
			case 5: 
				cout << "If the person were standing " << calculateDistanceToHitThePerson() << " meters away from the wall, the snowball would have hit the person. \n" << endl;
				break;
			case 6: 
				plotTrajectory();
				break;
			case 9:
				cout << "Closing the program...\n" << endl;
				return 0;
			default:
				cout << "Invalid operation please try again.\n" << endl;
				break;
		}
    }
}