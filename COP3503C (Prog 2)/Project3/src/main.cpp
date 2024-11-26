#include "board.h"
#include "config.h"
#include <cctype>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <utility>

void center_text(sf::Text &text, float x, float y) {
	sf::FloatRect text_rect = text.getLocalBounds();
	text.setOrigin(text_rect.left + text_rect.width / 2.0f,
				   text_rect.top + text_rect.height / 2.0f);
	text.setPosition(sf::Vector2f(x, y));
}

sf::Text new_text_object(sf::Font& font,
						 std::string text,
						 bool bold,
						 bool underlined,
						 const sf::Color& color,
						 unsigned int size,
						 float x,
						 float y) {
	sf::Text text_obj(text, font);
	text_obj.setCharacterSize(size);
	text_obj.setFillColor(color);
	center_text(text_obj, x, y);
	if (bold) {
		text_obj.setStyle(sf::Text::Bold);
	}
	if (underlined) {
		text_obj.setStyle(sf::Text::Underlined);
	}
	return text_obj;
}

void run_game_window(Config& cfg, std::string& name);

void run_welcome_window(Config& cfg) {
	const float width = (float)cfg.columns * 32;
	const float height = (float)cfg.rows * 32 + 100;
	sf::RenderWindow window(sf::VideoMode((int)width, (int)height), "Welcome Window", sf::Style::Close);
	window.setKeyRepeatEnabled(true);
	sf::RectangleShape rect;
	sf::Font font;
	if (!font.loadFromFile("./files/font.ttf")) {
		throw std::runtime_error("Could not load font from file.");
	}
	sf::Text welcome_text = new_text_object(
		font,
		"WELCOME TO MINESWEEPER!",
		true, true, sf::Color::White, 24, 
		width / 2, height / 2 - 150
	);
	sf::Text enter_name = new_text_object(
		font, "Enter your name:", true,
		false, sf::Color::White, 
		20, width / 2, height / 2 - 75);
	sf::Text dynamic_text_obj = new_text_object(
		font, "|", true,
		false, sf::Color::Yellow, 
		18, width / 2, height / 2 - 45);
	std::string user_typed_str;
	rect.setSize(sf::Vector2f(width, height));
	rect.setFillColor(sf::Color::Blue);
	bool has_entered_name = false;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (
				sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && 
				!user_typed_str.empty()
			) {
				has_entered_name = true;
				window.close();
			} else if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode >= 128) { // if it isn't letter input
					continue;
				} else if (
					std::isalpha(static_cast<char>(event.text.unicode)) && user_typed_str.size() < 10
				) {
					char curr = static_cast<char>(event.text.unicode);
					if (user_typed_str.empty()) {
						curr = (char)std::toupper(curr);
					} else {
						curr = (char)std::tolower(curr);
					}
					user_typed_str.push_back(curr);
					dynamic_text_obj = new_text_object(
						font, user_typed_str + "|", true,
						false, sf::Color::Yellow, 
						18, width / 2, height / 2 - 45);
				} else if (event.text.unicode == 8) {
					if (!user_typed_str.empty()) {
						user_typed_str.pop_back();
					}
					dynamic_text_obj = new_text_object(
						font, user_typed_str + "|", true,
						false, sf::Color::Yellow, 
						18, width / 2, height / 2 - 45);
				}
			}
		}
		window.clear();
		window.draw(rect);
		window.draw(welcome_text);
		window.draw(enter_name);
		window.draw(dynamic_text_obj);
		window.display();
	}
	if (has_entered_name) {
		run_game_window(cfg, user_typed_str);
	}
}

void run_game_window(Config& cfg, std::string& name) {
	const float width = (float)cfg.columns * 32;
	const float height = (float)cfg.rows * 32 + 100;
	sf::RenderWindow window(sf::VideoMode((int)width, (int)height), "Game Window", sf::Style::Close);
	Board board(cfg);
	board.print_as_str();
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(width, height));
	rect.setFillColor(sf::Color::White);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			window.clear();
			window.draw(rect);
			window.display();
		}
	}
}

void run_game() {
	Config cfg = get_config();
	run_welcome_window(cfg);
}

int main() {
	run_game();
	return 0;
}
