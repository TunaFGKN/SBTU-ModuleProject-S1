/*
    SBTU - Computer Engineering
    Module Project - Semester 1
    Tuna Figankaplan, Ali Bozkurt, Sude Yildirim, Burak Yalituna
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

const float PI = 3.14159;
float initialSpeed, angleA, angleB;
float speedAfterCollisionA, speedAfterCollisionB, energyLoss;

vector<float> calculateSpeedsAfterCollision(float initialSpeed, float angleA, float angleB) {
    float rate;
    rate = sin(angleB * PI / 180) / sin(angleA * PI / 180);
    speedAfterCollisionB = initialSpeed / (rate * cos(angleA * PI / 180) + cos(angleB * PI / 180));
    speedAfterCollisionA = rate * speedAfterCollisionB;
    vector<float> speedsAfterCollision = { speedAfterCollisionA, speedAfterCollisionB };
    return speedsAfterCollision;
}

float calculateEnergyLoss(float initialSpeed, float speedAfterCollisionA) {
    return 0.5 * (pow(initialSpeed, 2) - pow(speedAfterCollisionA, 2));
}

int main()
{
    cout << "Initial Speed (m/s): ";
    cin >> initialSpeed;

    cout << "Angle A (deg): ";
    cin >> angleA;

    cout << "Angle B (deg): ";
    cin >> angleB;

    speedAfterCollisionA = calculateSpeedsAfterCollision(initialSpeed, angleA, angleB)[0];
    speedAfterCollisionB = calculateSpeedsAfterCollision(initialSpeed, angleA, angleB)[1];
    energyLoss = calculateEnergyLoss(initialSpeed, speedAfterCollisionA);

    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << "1) Display speeds after collision.\n2) Display kinetic energy loss of Asteroid A.\n3) Plot trajectory.\n9) Exit.\nHello, please choose the option that you want to perform. Enter '9' to exit the program." << endl;
    cout << "------------------------------------------------------------------------------------------------------\n" << endl;

    while (true)
    {
        int option;
        cin >> option;
        switch (option)
        {
        case 1:
            cout << fixed << setprecision(3) << "Speed after collision of A: " << speedAfterCollisionA << "m/s" << endl << "Speed after collision of B: " << speedAfterCollisionB << "m/s \n" << endl;
            break;
        case 2:
            cout << fixed << setprecision(3) << "Kinetic energy loss is: " << energyLoss << "m J \n" << endl;
            break;
        case 3:
            cout << "\n";
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