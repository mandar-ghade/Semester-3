#pragma once
#include <iostream>
#include <vector>

class Vehicle {
    std::string make;
    std::string model;
    int year;
    float price;
    int mileage;
public:
    Vehicle(
        std::string make = "COP3503",
        std::string model = "Rust Bucket",
        int year = 1900,
        float price = 0,
        int mileage = 0
    ): make(make), model(model), year(year), price(price), mileage(mileage) {}
    void Display();
    std::string GetYearMakeModel();
    float GetPrice();
};
