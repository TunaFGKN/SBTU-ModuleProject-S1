#include <iostream>
#include <cmath>

using namespace std;

const float PI = 3.14159;
float initialSpeed, speedAfterCollisionA, speedAfterCollisionB, angleA, angleB;
float energyLoss;

int main()
{
    cout << "Initial Speed: ";
    cin >> initialSpeed;
    cout << "Angle A: ";
    cin >> angleA;
    cout << "Angle B: ";
    cin >> angleB;

    float rate;
    rate = sin(angleB * PI / 180) / sin(angleA * PI / 180);
    speedAfterCollisionB = initialSpeed / (rate * cos(angleA * PI / 180) + cos(angleB * PI / 180));
    speedAfterCollisionA = rate * speedAfterCollisionB;

    cout << "Speed after collision of A: " << speedAfterCollisionA << endl;
    cout << "Speed after collision of B: " << speedAfterCollisionB << endl;

    energyLoss = 0.5 * (pow(initialSpeed, 2) - pow(speedAfterCollisionA, 2));
    cout << "Kinetic energy loss is: " << energyLoss << "m J";

}