#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
    //User enterables----------------------------
    double rotormass = 10 * .5 / 6; // using 50% (.5 in second position. motor + rotor mass is 41% so adding 9% for struct) of DJI Matrice 600 Pro weight as reference, kg
    double mainmass = 10 - rotormass * 6; // non rotor mass of Matrice 600 Pro, kg
    double rotorthrust = 14 * 9.81; // using DJI E5000 motor as reference, kg * m/s^2
    double payloadThrust = 0.4; // percentage of thrust after weight subtraction used for payload, ie. 1 - % thrust for climb and maneuver
    int num = 10; // max number of rotors
    double rotorRad = .711 / 2; // radius of rotor, using E5000, meters
    //End user enterables------------------------

    double TW[num]; // thrust to weight ratio not including payload
    double mass;
    double thrust;
    double loadCap;
    double discLoad; // disc loading including max payload
    double percent; // percent change in thrust to weight

    cout << left << setw(10) << "Rotors" << setw(15) << "Thrust (N)" << setw(15) << "Mass (kg)" << setw(20) << "Thrust to Weight" << setw(15) << "% Change" << setw(20) << "Load Capacity (kg)" << "Disc Loading (kg/m^2)" << endl;

    for (int i = 1; i <= num; i++)
    {
        thrust = rotorthrust * i * 2;
        mass = mainmass + rotormass * i * 2;
        TW[i] = thrust / (mass * 9.81);
        percent = (TW[i] - TW[i - 1]) / TW[i - 1] * 100; // will be inf for initial run
        loadCap = (thrust - mass * 9.81) * payloadThrust / 9.81; // assumes some % of excess thrust for climb and manueverability ie. 1 - % of leftover thrust can be used for payload
        discLoad = (mass + loadCap) / (3.14159 * pow(rotorRad, 2) * i * 2); // uses E5000 rotor diameter specs, assumes full load capacity usage

        cout << left << setw(10) << i * 2 << setw(15) << thrust << setw(15) << mass << setw(20) << TW[i] << setw(15) << percent << setw(20) << loadCap << discLoad << endl;
    }
}