#pragma once
#include <iostream>
#include <vector>
#include "Showroom.h"

class Dealership {
    std::string name;
    unsigned int capacity;
    std::vector<Showroom> showrooms;
public:
    Dealership(
        std::string name = "Generic Dealership",
        unsigned int capacity = 0
    ): name(name), capacity(capacity) {}
    void AddShowroom(Showroom s);
    float GetAveragePrice();
    void ShowInventory();
};
