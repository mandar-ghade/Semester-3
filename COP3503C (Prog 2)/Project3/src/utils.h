#pragma once
#include <cctype>
#include <SFML/Graphics.hpp>


void center_text(sf::Text &text, float x, float y); 

sf::Text new_text_object(const sf::Font& font,
						 std::string text,
						 bool bold,
						 bool underlined,
						 const sf::Color& color,
						 unsigned int size,
						 float x,
						 float y); 

