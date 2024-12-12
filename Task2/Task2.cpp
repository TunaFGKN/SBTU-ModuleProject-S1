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

const float PI = 3.14159;
float initialSpeed, angleA, angleB;
float speedAfterCollisionA, speedAfterCollisionB, energyLoss;

vector<float> calculateSpeedsAfterCollision(float initialSpeed, float angleA, float angleB) {
    float rate = sin(angleB * PI / 180) / sin(angleA * PI / 180);

    speedAfterCollisionB = initialSpeed / (rate * cos(angleA * PI / 180) + cos(angleB * PI / 180));
    speedAfterCollisionA = rate * speedAfterCollisionB;

    return { speedAfterCollisionA, speedAfterCollisionB };
}

float calculateEnergyLoss(float initialSpeed, float speedAfterCollisionA) {
    return 0.5 * (pow(initialSpeed, 2) - pow(speedAfterCollisionA, 2));
}

void plotTrajectory() {
    Gnuplot gp("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persist");
    cout << "Calculating the trajectory..." << endl;
    vector<pair<float, float>> trajectoryA;
    vector<pair<float, float>> trajectoryB;

    // Zaman aralýðý ve yörünge hesaplamalarý
    for (float t = 0; t <= 10; t += 0.1) {

        // After Collision - Asteroid A
        float xA = speedAfterCollisionA * cos(angleA * PI / 180) * t;
        float yA = speedAfterCollisionA * sin(angleA * PI / 180) * t;
        trajectoryA.emplace_back(xA, yA);

        // After Collision - Asteroid B
        float xB = speedAfterCollisionB * cos(angleB * PI / 180) * t;
        float yB = (speedAfterCollisionB * sin(angleB * PI / 180) * t);
        trajectoryB.emplace_back(xB, yB);
    }

    // GNUplot plotting the graph.
    gp << "set title 'Asteroid Collision Trajectory After Collision'\n";
    gp << "set xlabel 'x (m)'\n";
    gp << "set ylabel 'y (m)'\n";
    gp << "set grid\n";
    gp << "plot '-' with lines title 'Asteroid A (After)', "
        "'-' with lines title 'Asteroid B (After)'\n ";        
    gp.send1d(trajectoryA);
    gp.send1d(trajectoryB);
}

bool validationCheck(float initialSpeed, float angleA, float angleB) {
    if (initialSpeed <= 0) return 0;
    if ((angleA || angleB > 90) && (angleA || angleB <= 0)) return 0;
    return 1;
}

int main()
{
    cout << "Initial Speed (m/s): ";
    cin >> initialSpeed;

    cout << "Angle A (deg): ";
    cin >> angleA;

    cout << "Angle B (deg): ";
    cin >> angleB;

    if (!validationCheck(initialSpeed, angleA, angleB)) {
        cout << "\nInvalid inputs. Please try again." << endl;
        return 0;
    }

    vector<float> speeds = calculateSpeedsAfterCollision(initialSpeed, angleA, angleB);
    speedAfterCollisionA = speeds[0];
    speedAfterCollisionB = speeds[1];
    energyLoss = calculateEnergyLoss(initialSpeed, speedAfterCollisionA);

    cout << fixed << setprecision(3);
    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << "1) Display speeds after collision.\n2) Display kinetic energy loss of Asteroid A.\n3) Plot trajectory.\n9) Exit.\nHello, please choose the option that you want to perform. Enter '9' to exit the program." << endl;
    cout << "------------------------------------------------------------------------------------------------------\n" << endl;

    while (true)
    {
        int option;
        cin >> option;
        switch (option)
        {
        case 0:
            cout << "Returning to the beginning...\n" << endl;
            main();
            return 0;
        case 1:
            cout << "Speed after collision of A: " << speedAfterCollisionA << "m/s" << endl << "Speed after collision of B: " << speedAfterCollisionB << "m/s \n" << endl;
            break;
        case 2:
            cout << "Kinetic energy loss is: " << energyLoss << "m J \n" << endl;
            break;
        case 3:
            plotTrajectory();
            cout << endl;
            break;        
        case 9:
            cout << "Closing the program...";
            return 0;
        default:
            cout << "Invalid operation please try again.\n" << endl;
            break;
        }
    }
}