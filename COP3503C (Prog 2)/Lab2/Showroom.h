#pragma once
#include <iostream>
#include <vector>
#include "Vehicle.h"

class Showroom {
    std::string name;
    std::vector<Vehicle> vehicles;
    unsigned int capacity;
public:
    Showroom(
        std::string name="Unnamed Showroom",
        unsigned int capacity = 0
    ): name(name), capacity(capacity) {} 
    std::vector<Vehicle> GetVehicleList();
    void AddVehicle(Vehicle v);
    void ShowInventory();
    float GetInventoryValue();
};

