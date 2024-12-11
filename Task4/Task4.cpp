/*
    SBTU - Computer Engineering
    Module Project - Semester 1
    Tuna Figankaplan, Ali Bozkurt, Sude Yildirim, Burak Yalituna
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include "gnuplot-iostream.h"

using namespace std;

const double G = 6.6743e-11;
const double PI = 3.14159;
double radius, massOfPlanet, altitude;
double satelliteVelocity, satellitePeriod;

double calculateVelocity(double massOfPlanet, double radius, double altitude) {
    return sqrt((G * massOfPlanet) / (radius + altitude));
}

double calculatePeriod(double radius, double altitude, double velocity) {
    return (2 * PI * (radius + altitude)) / velocity;
    // return sqrt((4 * pow(PI, 2) * pow(radius + altitude, 3)) / (G * massOfPlanet));
}

void simulateOrbit() {
    cout << endl;
}

bool validationCheck(float radius, float massOfPlanet, float altitude) {
    // if ( <= 0) return 0;
    return 1;
}

int main()
{
    cout << "Enter radius of the planet (m): ";
    cin >> radius;

    cout << "Enter mass of the planet (kg): ";
    cin >> massOfPlanet;

    cout << "Enter altitude of the satellite from the planet (m): ";
    cin >> altitude;

    satelliteVelocity = calculateVelocity(massOfPlanet, radius, altitude);
    satellitePeriod = calculatePeriod(radius, altitude, satelliteVelocity);

    cout << fixed << setprecision(3);
    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << "1) Find the satellite's orbital velocity.\n2) Find the satellite's period.\n3) Simulate satellite orbits around the planet.\n9) Exit.\nHello, please choose the option that you want to perform. Enter '9' to exit the program." << endl;
    cout << "------------------------------------------------------------------------------------------------------\n" << endl;

    while (true) {
        int option;
        cin >> option;

        switch (option)
        {
        case 1:
            cout << "Satellite Velocity: " << satelliteVelocity << endl << endl;
            break;
        case 2:
            cout << "Satellite Period: " << satellitePeriod << endl << endl;
            break;
        case 3:
            simulateOrbit();
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