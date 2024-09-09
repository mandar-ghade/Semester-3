#include "Dealership.h"

void Dealership::AddShowroom(Showroom s) {
    if (this->showrooms.size() < this->capacity) {
        this->showrooms.push_back(s);
    } else {
        std::cout << "Dealership is full, can't add another showroom!\n";
    }
}

float Dealership::GetAveragePrice() {
    float total_avg = 0;
    size_t count = 0;
    if (this->showrooms.size() != 0) {
        for (Showroom showroom: this->showrooms) {
            auto vehicles = showroom.GetVehicleList();
            count += vehicles.size();
            total_avg += showroom.GetInventoryValue();
        }
    }
    total_avg /= (float) (count == 0 ? 1 : count);
    return total_avg;
}

void Dealership::ShowInventory() {
    if (this->showrooms.size() == 0) {
        std::cout << this->name << " is empty!\n";
    }
    for (Showroom showroom: this->showrooms) {
        showroom.ShowInventory();
        std::cout << '\n';
    }
    std::cout << "Average car price: $" << this->GetAveragePrice();
}

