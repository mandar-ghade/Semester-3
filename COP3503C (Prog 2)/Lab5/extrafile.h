#pragma once
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

class Weapon {
	std::string name;
	int rating;
	float consumption;
	static Weapon deserialize(std::fstream& stream) {
		if (!stream.is_open()) {
			throw std::runtime_error("Stream was closed unexpectedly.");
		}

		int name_length;

		stream.read(reinterpret_cast<char*>(&name_length), 4);

		char* name = new char[name_length];

		stream.read(name, name_length);

		std::string name_str(name);

		delete[] name;

		int rating;
		float consumption;

		stream.read(reinterpret_cast<char*>(&rating), sizeof(int));
		stream.read(reinterpret_cast<char*>(&consumption), sizeof(float));

		Weapon new_weapon(name_str, rating, consumption);
		return new_weapon;
	}
public:
	Weapon(
		std::string name, 
		int rating, 
		float consumption
	): name(name), rating(rating), consumption(consumption) {};
	void print() const {
		std::cout << name << ", " << rating << ", " << consumption << '\n';
	}
	std::string get_name() const {
		return name;
	}
	int get_rating() const {
		return rating;
	}
	float get_consumption() const {
		return consumption;
	}
	static std::vector<Weapon> from_stream(std::fstream& stream) {
		if (!stream.is_open()) {
			throw std::runtime_error("Stream was closed unexpectedly.");
		}
		int count;
		stream.read(reinterpret_cast<char*>(&count), 4);
		std::vector<Weapon> inventory;
		for (int i = 0; i < count; i++) {
			inventory.push_back(Weapon::deserialize(stream));
		}
		return inventory;
	}
};

class Ship {
	const std::string name;
	const std::string cls;
	const short ship_len;
	const int shield_capacity;
	const float max_warp_speed;
	const std::vector<Weapon> inventory;
	static Ship deserialize(std::fstream& stream) {
		if (!stream.is_open()) {
			throw std::runtime_error("Stream was closed unexpectedly.");
		}

		int name_length;

		stream.read(reinterpret_cast<char*>(&name_length), 4);

		char* name = new char[name_length];

		stream.read(name, name_length);

		std::string name_str(name);
		delete[] name;

		int class_length;

		stream.read(reinterpret_cast<char*>(&class_length), 4);

		char* cls = new char[class_length];

		stream.read(cls, class_length);

		std::string cls_str(cls);
		delete[] cls;

		short ship_len;
		int shield_capacity;
		float max_warp_speed;

		stream.read(reinterpret_cast<char*>(&ship_len), sizeof(short));
		stream.read(reinterpret_cast<char*>(&shield_capacity), sizeof(int));
		stream.read(reinterpret_cast<char*>(&max_warp_speed), sizeof(float));

		std::vector<Weapon> inventory = Weapon::from_stream(stream);

		Ship new_ship(name_str, cls_str, ship_len, shield_capacity, max_warp_speed, inventory);
		
		return new_ship;
	}
public:
	Ship(
		const std::string name,
		const std::string cls,
		const short ship_len,
		const int shield_capacity,
		const float max_warp_speed,
		const std::vector<Weapon> inventory
	): name(name), cls(cls), 
		ship_len(ship_len), shield_capacity(shield_capacity),
		max_warp_speed(max_warp_speed), inventory(inventory) {};
	std::vector<Weapon> get_inventory() const {
		return inventory;
	}
	Weapon get_strongest_weapon() const {
		if (inventory.size() == 0) {
			throw std::runtime_error("Inventory is empty");
		}
		Weapon strongest = inventory.at(0);
		for (Weapon weapon: inventory) {
			if (weapon.get_rating() > strongest.get_rating()) {
				strongest = weapon;
			}
		}
		return strongest;
	}
	int get_total_rating() const {
		int total_rating = 0;
		for (const Weapon& weapon: inventory) {
			total_rating += weapon.get_rating();
		}
		return total_rating;
	}
	void print_weapons() const {
		int total_rating = 0;
		for (const Weapon& weapon: inventory) {
			weapon.print();
			total_rating += weapon.get_rating();
		}
		std::cout << "Total firepower: " << total_rating << '\n';
	}
	void print() const {
		std::cout << "Name: " << name << '\n';
		std::cout << "Class: " << cls << '\n';
		std::cout << "Length: " << ship_len << '\n';
		std::cout << "Shield capacity: " << shield_capacity << '\n';
		std::cout << "Maximum Warp: " << max_warp_speed << '\n';
		std::cout << "Armaments: \n";
		if (inventory.size() == 0) {
			std::cout << "Unarmed\n";
		} else {
			print_weapons();
		}
	}
	static std::vector<Ship> from_stream(std::fstream& stream) {
		if (!stream.is_open()) {
			throw std::runtime_error("Stream was closed unexpectedly.");
		}
		int count;
		stream.read(reinterpret_cast<char*>(&count), 4);
		std::vector<Ship> ships;
		for (int i = 0; i < count; i++) {
			ships.push_back(Ship::deserialize(stream));
		}
		return ships;
	}
};

