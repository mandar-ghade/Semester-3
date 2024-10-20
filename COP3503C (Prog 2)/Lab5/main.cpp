#include <iostream>
#include <fstream>
#include "extrafile.h"
using namespace std;

void print_all_ships(std::vector<Ship>& ships) {
	if (ships.size() == 0) return;
	for (const Ship& ship: ships) {
		ship.print();
		std::cout << '\n';
	}
}

void print_strongest_ship_by_weapon(std::vector<Ship>& ships) {
	if (ships.size() == 0) return;
	Ship* strongest = &ships.at(0);
	for (Ship& ship: ships) {
		if (ship.get_inventory().size() == 0) {
			continue;
		} else if (ship.get_strongest_weapon().get_rating() > strongest->get_strongest_weapon().get_rating()) {
			strongest = &ship;
		}
	}
	strongest->print();
}

void print_strongest_ship_by_rating(std::vector<Ship>& ships) {
	if (ships.size() == 0) return;
	Ship* strongest = &ships.at(0);
	for (Ship& ship: ships) {
		if (ship.get_inventory().size() == 0) {
			continue;
		} else if (ship.get_total_rating() > strongest->get_total_rating()) {
			strongest = &ship;
		}
	}
	strongest->print();
}

void print_weakest_by_rating(std::vector<Ship>& ships) {
	if (ships.size() == 0) return;
	Ship* weakest = &ships.at(0);
	for (Ship& ship: ships) {
		if (ship.get_inventory().size() == 0) {
			continue;
		} else if (ship.get_total_rating() < weakest->get_total_rating()) {
			weakest = &ship;
		}
	}
	weakest->print();
}

void print_unarmed_ships(std::vector<Ship>& ships) {
	if (ships.size() == 0) return;
	for (const Ship& ship: ships) {
		if (ship.get_inventory().size() == 0) {
			ship.print();
			std::cout << '\n';
		}
	}
}


int main()
{
	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;

	std::vector<Ship> ships;
	std::fstream friendly_ships_file("friendlyships.shp", ios_base::in | ios_base::binary);
	std::fstream enemy_ships_file("enemyships.shp", ios_base::in | ios_base::binary);

	if (option == 1) {
		ships = Ship::from_stream(friendly_ships_file);
	} else if (option == 2) {
		ships = Ship::from_stream(enemy_ships_file);
	} else if (option == 3) {
		ships = Ship::from_stream(friendly_ships_file);
		std::vector<Ship> enemy_ships = Ship::from_stream(enemy_ships_file);
		for (Ship enemy_ship: enemy_ships) {
			ships.push_back(enemy_ship);
		}
	} else {
		throw std::runtime_error("Option not found.");
	}

	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;
	
	cin >> option;
	
	if (option == 1) {
		print_all_ships(ships);
	} else if (option == 2) {
		print_strongest_ship_by_weapon(ships);
	} else if (option == 3) {
		print_strongest_ship_by_rating(ships);
	} else if (option == 4) {
		print_weakest_by_rating(ships);
	} else if (option == 5) {
		print_unarmed_ships(ships);
	} else {
		throw std::runtime_error("Option not found.");
	}
	
   return 0;
}
