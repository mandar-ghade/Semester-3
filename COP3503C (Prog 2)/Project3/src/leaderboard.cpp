#include "leaderboard.h"
#include "stdio.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <tuple>

void sort_players_by_time(std::vector<Player>& players) {
    std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        return a.time < b.time; // Sort in ascending order of time
    });
}

std::string to_readable_str(Leaderboard* lb, Player& player, int idx) {
	auto time_as_str = time_to_str(&player);
	std::string output_str = std::to_string(idx + 1);
	output_str += ".\t\t";
	output_str += std::get<0>(time_as_str) + ":";
	output_str += std::get<1>(time_as_str);
	output_str += "\t\t";
	output_str += player.name;
	if (lb->new_player_replaced) {
		if (lb->new_player_time == player.time &&
			lb->new_player_name == player.name) {
			output_str += '*';
		}
	}
	return output_str;
}

std::string get_leaderboard_str(Leaderboard* leaderboard) {
	std::string output_str;
	sort_players_by_time(leaderboard->players);
	int i = 0;
	for (auto p: leaderboard->players) {
		output_str += to_readable_str(leaderboard, p, i++) + "\n\n";
	}
	return output_str;
}

int to_digit(char c) {
	return c - '0';
}

std::string to_string(Player& player) {
	auto time_as_str = time_to_str(&player);
	std::string output_str;
	output_str += std::get<0>(time_as_str) + ":";
	output_str += std::get<1>(time_as_str) + ",";
	output_str += player.name;
	return output_str;
}

void write_to_file(Leaderboard* leaderboard) {
	std::ofstream stream("./files/leaderboard.txt");
	if (!stream.is_open()) {
		throw std::runtime_error("Could not open leaderboard file.");
	}
	sort_players_by_time(leaderboard->players);
	for (auto p: leaderboard->players) {
		stream << to_string(p) << '\n';
	}
}

void remove_from_file_and_lb(Player& player, Leaderboard* leaderboard) {
	std::vector<Player> players;
	sort_players_by_time(leaderboard->players);
	for (size_t i = 0; i < leaderboard->players.size(); i++) {
		Player p = leaderboard->players.at(i);
		if (player.name == p.name && player.time == p.time) {
			continue;
		}
		players.push_back(p);
	}
	leaderboard->players = players;
	write_to_file(leaderboard);
}

void add_to_file_and_lb(Player& player, Leaderboard* leaderboard) {
	leaderboard->players.push_back(player);
	leaderboard->new_player_replaced = true;
	leaderboard->new_player_name = player.name;
	leaderboard->new_player_time = player.time;
	write_to_file(leaderboard);
}

void set_no_new_player_replaced(Leaderboard* leaderboard) {
	leaderboard->new_player_replaced = false;
}

void replace_lowest_score(Player& player, Leaderboard* leaderboard) {
	if (leaderboard->players.size() < 5) {
		add_to_file_and_lb(player, leaderboard);
		return;
	}
	for (size_t i = 0; i < leaderboard->players.size(); i++) {
		Player& p = leaderboard->players.at(i);
		if (player.name == p.name && player.time == p.time) {
			continue;
		}
		if (player.time < p.time) {
			remove_from_file_and_lb(p, leaderboard);
			add_to_file_and_lb(player, leaderboard);
			return;
		}
	}
	leaderboard->new_player_replaced = false;
	return;
}

void add_winner(std::string name, int secs, Leaderboard* leaderboard) {
	Player player = {
		.name = name,
		.time = secs
	};
	replace_lowest_score(player, leaderboard);
}

int from_str_to_secs(std::string input_str) {
	int secs = 0;
	std::istringstream ss(input_str);
	std::string mins_str, secs_str;
	getline(ss, mins_str, ':');
	getline(ss, secs_str);
	if (mins_str.empty() || secs_str.empty()) {
		throw std::runtime_error("Mins or secs is empty!");
	}
	secs += std::stoi(mins_str) * 60; // handles trailing zeros apparently.
	secs += std::stoi(secs_str);
	return secs;
}

std::string trim(const std::string& str) {
	// stackoverflow
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

Leaderboard parse() {
	std::ifstream stream("./files/leaderboard.txt");
	if (!stream.is_open()) {
		throw std::runtime_error("Leaderboard file not found!");
	}
	std::vector<Player> players;
	std::string line;
	int i = 0;
	while (getline(stream, line)) {
		i++;
		if (i > 5) {
			break;
		}
		if (line.empty()) {
			continue;
		}
		std::istringstream ss(line);
		std::string time;
		std::string name;
		getline(ss, time, ',');
		getline(ss, name);
		time = trim(time);
		name = trim(name);
		players.push_back(
			Player {
				.name = name,
				.time = from_str_to_secs(time)
			}
		);
	}
	return Leaderboard {
		.players = players,
		.new_player_replaced = false,
		.new_player_name = "",
		.new_player_time = 0,
	};
}

std::tuple<std::string, std::string> time_to_str(Player* player) {
	// gets time separated by min and sec
	int mins_elapsed = static_cast<int>(std::floor(player->time / 60)); 
	int secs_elapsed = static_cast<int>(player->time) % 60;
	std::string mins_str;
	std::string secs_str;
	if (mins_elapsed < 10) {
		mins_str += "0";
	}
	if (secs_elapsed < 10) {
		secs_str += "0";
	}
	mins_str += std::to_string(mins_elapsed);
	secs_str += std::to_string(secs_elapsed);
	return {mins_str, secs_str};
}

