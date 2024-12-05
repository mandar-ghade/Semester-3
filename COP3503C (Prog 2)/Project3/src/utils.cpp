#include <cctype>
#include <SFML/Graphics.hpp>


void center_text(sf::Text &text, float x, float y) {
	sf::FloatRect text_rect = text.getLocalBounds();
	text.setOrigin(text_rect.left + text_rect.width / 2.0f,
				   text_rect.top + text_rect.height / 2.0f);
	text.setPosition(sf::Vector2f(x, y));
}

sf::Text new_text_object(const sf::Font& font,
						 std::string text,
						 bool bold,
						 bool underlined,
						 const sf::Color& color,
						 unsigned int size,
						 float x,
						 float y) {
	sf::Text text_obj;
	text_obj.setString(text);
	text_obj.setFont(font);
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

