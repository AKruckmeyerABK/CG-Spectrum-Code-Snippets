// Inheritance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
class Vehicle
{
protected:
    string brand = "N/A";
public:
    Vehicle(string _brand)
    {
        brand = _brand;
    }

    virtual void Drive() = 0;
};

class Boat : public Vehicle
{
protected:
    float buoyancy = 0;
public:
    Boat(string _brand, float _buoyancy) : Vehicle(_brand), buoyancy(_buoyancy){}

    void Drive() override
    {
        if(buoyancy <= 0)
            cout << "Blub blub blub." << endl;
        else
            cout << "Sploosh, sploosh." << endl;
    }
};

class Car : public Vehicle
{
protected:
    float tirePSI = 0;
public:
    Car(string _brand, float _tirePSI) : Vehicle(_brand), tirePSI(_tirePSI) {}
    void Drive() override
    {
        if (tirePSI <= 0)
            cout << "SCCRRRRRRRRCCCHHHH!!!" << endl;
        else
            cout << "Vroom, Vroom." << endl;
    }
};

class Airplane : public Vehicle
{
protected:
    unsigned int engineCount = 0;
public:
    Airplane(string _brand, float _engineCount) : Vehicle(_brand), engineCount(_engineCount) {}

    void Drive() override
    {
        if (engineCount == 0)
            cout << "Yeah, this thing isn't taking off." << endl;
        else if (engineCount % 2 == 1)
            cout << "WOOOOOSH... PRRHHHM BOOOOOM!" << endl;
        else
            cout << "WOOOOOSH" << endl;
    }
};

int main()
{
    Vehicle* vehArray[7];

    vehArray[0] = new Boat("WaveRace", 0);
    vehArray[1] = new Boat("WaveRace", 1);
    vehArray[2] = new Car("KIA", 0);
    vehArray[3] = new Car("KIA", 1);
    vehArray[4] = new Airplane("Boeing", 3);
    vehArray[5] = new Airplane("Boeing", 0);
    vehArray[6] = new Airplane("Boeing", 4);

    for (int i = 0; i < 7; i++)
    {
        vehArray[i]->Drive();
    }
}