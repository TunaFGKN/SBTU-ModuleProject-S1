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

// Declaring variables
const float GRAVITY = 9.8;
const float PI = 3.14159;
float initialSpeed, angle, height, ftime, impactPoint;
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

// Returns the x and y components of the position vector at an exact time as a vector.
vector<float> positionVectorOverTime(float t) {
	vector<float> component = {initialSpeed * cos(radian) * t, (initialSpeed * sin(radian) * t) + (GRAVITY / 2 * t * t)};
	return component;
}

void positionVectorOutputHandler(float time = 1) {
	cout << ftime * time << " seconds: R = (" << positionVectorOverTime(ftime * time)[0] << "i - " << positionVectorOverTime(ftime * time)[1] << "j) m" << endl;
}

void plotTrajectory() {
	// Create GNUPlot object
	Gnuplot gp("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persist");

	vector<pair<float, float>> trajectoryData; // X ve Y koordinatlarý

	float timeStep = 0.01; // Time step
	for (float t = 0; t <= ftime; t += timeStep) {
		float x = initialSpeed * cos(radian) * t; // X coordinate
		float y = (-initialSpeed * sin(radian) * t) - (0.5 * GRAVITY * t * t); // Y coordinate

		if (x == impactPoint) break; // stop when it touches the ground

		trajectoryData.push_back(make_pair(x, y)); // Data
	}

	// GNUPlot commands
	gp << "set title 'Projectile Motion Trajectory'\n";
	gp << "set xlabel 'Horizontal Distance (m)'\n";
	gp << "set ylabel 'Vertical Distance (m)'\n";
	gp << "plot '-' with lines title 'Trajectory'\n";

	// TSend data to gnuplot
	gp.send1d(trajectoryData);

	cout << "Trajectory plotted successfully!\n" << endl;
}

float calculateDistanceToHitThePerson() {
	return initialSpeed * cos(radian) * solveForQuadraticEquation(GRAVITY / 2, initialSpeed * sin(radian), -height + 1.9);
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
	impactPoint = (initialSpeed * cos(radian)) * ftime;

	cout << "------------------------------------------------------------------------------------------------------" << endl;
	cout << "1) Display the time of flight.\n2) Find the impact point.\n3) Horizontal and vertical coordinates of the snowball's motion over time.\n4) Decide if the snowball will hit the person or not.\n5) Exact distance at which the snowball will hit a person standing at a specified distance and height.\n6) Plot the trajectory.\n9) Exit\nHello, please choose the option that you want to perform. Enter '9' to exit the program." << endl;
	cout << "------------------------------------------------------------------------------------------------------\n" << endl;

	while (true) {
		char option;
		cin >> option;

		switch (option)
		{
			/*case 0:
			cout << "Returning to the beginning...\n" << endl;
			main();
			return 0;*/			
			case '1': // Flight time
				cout << fixed << setprecision(3) << "Flight time is " << ftime << " seconds.\n" << endl;
				break;
			case '2': // Impact point
				cout << fixed << setprecision(3) << "The ball will hit the ground " << impactPoint << " meters away from the edge of the barn.\n" << endl;
				break;
			case '3': // Position vector over 4 time intervals
				positionVectorOutputHandler(0.25);
				positionVectorOutputHandler(0.5);
				positionVectorOutputHandler(0.75);
				positionVectorOutputHandler(1);
				cout << endl;
				break;
			case '4': // Determine if the ball hits the person
				if (impactPoint < 4) {
					cout << "Snowball will not hit the person." << endl;
					break;
				}
				if (calculateDistanceToHitThePerson() < 4) {
					cout << "\aSnowball will hit the person." << endl;
				}
				else {
					cout << "Snowball will not hit the person." << endl;
				}
				cout << endl;
				break;
			case '5': // Exact Distance
				cout << "If the person were standing " << calculateDistanceToHitThePerson() << " meters away from the wall, the snowball would have hit the person. \n" << endl;
				break;
			case '6': // Plot trajectory
				plotTrajectory();
				break;
			case '9':
				cout << "Closing the program...\n" << endl;
				return 0;
			default:
				cout << "Invalid operation please try again.\n" << endl;
				break;
		}
    }
}