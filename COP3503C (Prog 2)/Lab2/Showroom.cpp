#include "Showroom.h"
std::vector<Vehicle> Showroom::GetVehicleList() {
    return this->vehicles;
}

void Showroom::AddVehicle(Vehicle v) {
    if (this->vehicles.size() < this->capacity) {
        this->vehicles.push_back(v);
    } else {
        std::cout << "Showroom is full! Cannot add " << v.GetYearMakeModel() << '\n';
        // this->ShowInventory();
    }
}

void Showroom::ShowInventory() {
    if (this->vehicles.size() == 0) {
        std::cout << this->name << " is empty!\n";
        return; // just added
    }
    std::cout << "Vehicles in " << this->name << '\n'; 
    for (Vehicle vehicle: this->vehicles) {
        vehicle.Display();
    }
}

float Showroom::GetInventoryValue() {
    float inventory_value = 0;
    for (Vehicle vehicle: this->vehicles) {
        inventory_value += vehicle.GetPrice();
    }
    return inventory_value;
}

