#pragma once
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

struct Player {
	std::string name;
	int time;
};

struct Leaderboard {
	std::vector<Player> players;
	bool new_player_replaced;
	std::string new_player_name;
	int new_player_time;
};

std::string to_string(Player& player); 
void set_no_new_player_replaced(Leaderboard* leaderboard);
std::string get_leaderboard_str(Leaderboard* leaderboard);
int from_str_to_secs(std::string input_str);
void add_winner(std::string name, int secs, Leaderboard* leaderboard);
std::tuple<std::string, std::string> time_to_str(Player* player); 
Leaderboard parse();
