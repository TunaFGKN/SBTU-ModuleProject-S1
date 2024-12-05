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

// Returns the x and y components of the position vector at an exact time as a vector.
vector<float> positionVectorOverTime(float t) {
	vector<float> component = {initialSpeed * cos(radian) * t, (initialSpeed * sin(radian) * t) + (GRAVITY / 2 * t * t)};
	return component;
}

void positionVectorOutputHandler(float time = 1) {
	cout << ftime * time << " seconds: R = (" << positionVectorOverTime(ftime * time)[0] << "i - " << positionVectorOverTime(ftime * time)[1] << "j) m" << endl;
}

void plotTrajectory() {
	// GNUPlot nesnesi oluþtur
	Gnuplot gp("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persist");

	// Verileri GNUPlot'a direkt olarak besle
	vector<pair<float, float>> trajectoryData; // X ve Y koordinatlarý

	float timeStep = 0.01; // Zaman adýmý
	for (float t = 0; t <= ftime; t += timeStep) {
		float x = initialSpeed * cos(radian) * t; // X koordinatý
		float y = (-initialSpeed * sin(radian) * t) - (0.5 * GRAVITY * t * t); // Y koordinatý

		if (x == _distance) break; // Yere düþtüðünde döngüyü durdur.

		trajectoryData.push_back(make_pair(x, y)); // Verileri vektöre ekle
	}

	// GNUPlot komutlarý
	gp << "set title 'Projectile Motion Trajectory'\n";
	gp << "set xlabel 'Horizontal Distance (m)'\n";
	gp << "set ylabel 'Vertical Distance (m)'\n";
	gp << "plot '-' with lines title 'Trajectory'\n";

	// Trajektori verilerini GNUPlot'a gönder
	gp.send1d(trajectoryData);

	cout << "Trajectory plotted successfully!\n" << endl;
	
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
	cout << "1) Display the time of flight.\n2) Find the impact point.\n3) Horizontal and vertical coordinates of the snowball's motion over time.\n4) Decide if the snowball will hit the person or not.\n5) Exact distance at which the snowball will hit a person standing at a specified distance and height.\n6) Plot the trajectory.\n9) Exit\nHello, please choose the option that you want to perform. Enter '9' to exit the program." << endl;
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
			case '3': // Position vector over 4 time intervals
				positionVectorOutputHandler(0.25);
				positionVectorOutputHandler(0.5);
				positionVectorOutputHandler(0.75);
				positionVectorOutputHandler(1);
				cout << endl;
				break;
			case '4': // 
				cout << "\n" << endl;
				break;
			case '5': // 
				cout << "\n" << endl;
				break;
			case '6':
				plotTrajectory();
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