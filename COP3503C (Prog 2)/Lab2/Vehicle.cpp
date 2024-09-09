#include <iostream>
#include "Vehicle.h"

void Vehicle::Display() {
    std::cout << this->GetYearMakeModel() << " $" << this->price << ' ' << this->mileage << '\n';
};

std::string Vehicle::GetYearMakeModel() {
    return std::to_string(this->year) + ' ' + this->make + ' ' + this->model;
}

float Vehicle::GetPrice() {
    return this->price;
}

