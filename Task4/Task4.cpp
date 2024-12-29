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
}

void plotPositionTimeGraph() {
    cout << "Calculating the Position - Time graph...\n" << endl;
    Gnuplot gp("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persist");
    float omega = 2 * PI / satellitePeriod;
    vector<pair<float, float>> x_t, y_t;
    for (int i = 0; i < 1000; ++i)
    {
        float t = satellitePeriod * i / (1000-1);
        float x = (radius + altitude) * cos(omega * t);
        float y = (radius + altitude) * sin(omega * t);
        x_t.push_back(make_pair(t, x));
        y_t.push_back(make_pair(t, y));
    }
    gp << "set terminal qt size 800,600\n";
    gp << "set title 'Position-Time Graphs'\n";
    gp << "set xlabel 'Time (s)'\n";
    gp << "set ylabel 'Position (m)'\n";
    gp << "set grid\n";
    gp << "plot '-' using 1:2 with lines title 'x(t) = r * cos(wt)', "
        "'-' using 1:2 with lines title 'y(t) = r * sin(wt)'\n";
    gp.send1d(x_t);  // X(t) data
    gp.send1d(y_t);  // Y(t) data
}

void plotOrbit() {
    cout << "Calculating the orbit...\n" << endl;
    Gnuplot gp("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persist");
    float omega = 2 * PI / satellitePeriod;
    vector<pair<float, float>> xy;
    for (int i = 0; i < 1000; ++i)
    {
        float t = satellitePeriod * i / (1000 - 1);
        float x = (radius + altitude) * cos(omega * t);
        float y = (radius + altitude) * sin(omega * t);
        xy.push_back(make_pair(x, y));
    }
    gp << "set terminal qt size 800,800\n";
    gp << "set xlabel 'X Position (s)'\n";
    gp << "set ylabel 'Y Position (m)'\n";
    gp << "set grid\n";
    gp << "set size ratio -1\n";
    gp << "plot '-' with lines title 'Satellite Orbit'\n";
    gp.send1d(xy);
}


bool validationCheck(float radius, float massOfPlanet, float altitude) {
    if (radius <= 0 || massOfPlanet <= 0 || altitude <= 0) return 0;
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

    if (!validationCheck(radius, massOfPlanet, altitude)) {
        cout << "\nInvalid inputs. Please try again." << endl;
        return 0;
    }

    satelliteVelocity = calculateVelocity(massOfPlanet, radius, altitude);
    satellitePeriod = calculatePeriod(radius, altitude, satelliteVelocity);

    cout << fixed << setprecision(3);
    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << "1) Find the satellite's orbital velocity.\n2) Find the satellite's period.\n3) Plot Position - Time graphs.\n4) Simulate satellite orbits around the planet.\n9) Exit.\nHello, please choose the option that you want to perform. Enter '9' to exit the program." << endl;
    cout << "------------------------------------------------------------------------------------------------------\n" << endl;

    while (true) {
        int option;
        cout << "Choose option: ";
        cin >> option;

        switch (option)
        {
        case 0:
            cout << "Returning to the beginning...\n" << endl;
            main();
            return 0;
        case 1:
            cout << "Satellite Velocity: " << satelliteVelocity << "m/s" << endl << endl;
            break;
        case 2:
            cout << "Satellite Period: " << satellitePeriod << "s" << endl << endl;
            break;
        case 3:
            plotPositionTimeGraph();
            break;
        case 4:
            plotOrbit();
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