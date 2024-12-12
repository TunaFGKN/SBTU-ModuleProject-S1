/*
    SBTU - Computer Engineering
    Module Project - Semester 1
    Tuna Figankaplan, Ali Bozkurt, Sude Yildirim, Burak Yalituna
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "gnuplot-iostream.h"

using namespace std;

const float GRAVITY = 9.8;
const float PI = 3.14159;
float initialSpeed, massOfBullet, massOfPendulum, pendulumLength;
float commonSpeed, dHeight, kineticEnergyBullet, kineticEnergyCombined;

float findCommonSpeed(float initialSpeed, float massOfBullet, float massOfPendulum) {
    return (initialSpeed * massOfBullet) / (massOfBullet + massOfPendulum);
}

float findHeight(float commonSpeed) {
    return (commonSpeed * commonSpeed) / (2 * GRAVITY);
}

vector<float> findKineticEnergy(float massOfBullet, float initialSpeed, float massOfPendulum, float commonSpeed) {
    float kineticEnergy1 = 0.5 * massOfBullet * pow(initialSpeed, 2);
    float kineticEnergy2 = 0.5 * (massOfBullet + massOfPendulum) * pow(commonSpeed, 2);
    vector<float> kineticEnergies = { kineticEnergy1, kineticEnergy2 };
    return kineticEnergies;
}

void plotSwingPath() {
    cout << "Calculating the path...\n" << endl;
    Gnuplot gp("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persist");

    float thetaMax = acos(1 - dHeight / pendulumLength);
    vector<float> time, x, y;
    for (int i = 0; i < 500; ++i)
    {
        float t = 2 * PI * i / (500 - 1);
        float theta = thetaMax * cos(t);
        float x_pos = pendulumLength * sin(theta);
        float y_pos = -pendulumLength * cos(theta);

        time.push_back(t);
        x.push_back(x_pos);
        y.push_back(y_pos);
    }

    gp << "set title 'Trajectory After Collision'\n";
    gp << "set xlabel 'X Position (m)'\n";
    gp << "set ylabel 'Y Position (m)'\n";
    gp << "set grid\n";
    gp << "set key left top\n";
    gp << "plot '-' with lines title 'Swing Path' \n";
        
    gp.send1d(make_pair(x,y));
}

bool validationCheck(float initialSpeed, float massOfBullet, float massOfPendulum, float pendulumLength) {
    if (initialSpeed <= 0 || massOfBullet <= 0 || massOfPendulum <= 0 || pendulumLength <= 0) return 0;
    return 1;
}

int main()
{
    cout << "Enter initial speed (m/s): ";
    cin >> initialSpeed;

    cout << "Enter the mass of the bullet (kg): ";
    cin >> massOfBullet;

    cout << "Enter the mass of the pendulum (kg): ";
    cin >> massOfPendulum;

    cout << "Enter the length of the pendulum (m): ";
    cin >> pendulumLength;

    if (!validationCheck(initialSpeed, massOfBullet, massOfPendulum, pendulumLength)) {
        cout << "\nInvalid inputs. Please try again." << endl;
        return 0;
    }

    commonSpeed = findCommonSpeed(initialSpeed, massOfBullet, massOfPendulum);
    dHeight = findHeight(commonSpeed);
    kineticEnergyBullet = findKineticEnergy(massOfBullet, initialSpeed, massOfPendulum, commonSpeed)[0];
    kineticEnergyCombined = findKineticEnergy(massOfBullet, initialSpeed, massOfPendulum, commonSpeed)[1];

    cout << fixed << setprecision(3);
    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << "1) Find the common speed.\n2) Find the vertical height reached by the pendulum after the collision.\n3) Find the kinetic energy of bullet before collision.\n4) Find the combined kinetic energy after collision.\n5) Plot the path.\n9) Exit.\nHello, please choose the option that you want to perform. Enter '9' to exit the program." << endl;
    cout << "------------------------------------------------------------------------------------------------------\n" << endl;

    while (true)
    {
        int option;
        cin >> option;
        switch (option) {
        case 0:
            cout << "Returning to the beginning...\n" << endl;
            main();
            return 0;
        case 1:
            cout << "Common Speed: " << commonSpeed << " m/s \n"<< endl;
            break;
        case 2:
            cout << "Vertical height reached by the pendulum after the collision: " << dHeight << " m \n" << endl;
            break;
        case 3:
            cout << "Kinetic energy of bullet before collision: " << kineticEnergyBullet << " J \n" << endl;
            break;
        case 4:
            cout << "Combined kinetic energy after collision: " << kineticEnergyCombined << " J \n" << endl;
            break;
        case 5:
            plotSwingPath();
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