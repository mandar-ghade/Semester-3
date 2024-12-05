#pragma once
#include "board.h"
#include "config.h"
#include "leaderboard.h"
#include "tile.h"
#include "utils.h"
#include <chrono>
#include <cmath>

enum GAME_STATE {
	IN_PROGRESS,
	PAUSED,
	LOSS,
	WIN,
};


class Game {
private:
	GAME_STATE state;
	Board board;
	const Config* cfg;
	const std::string name;
	sf::RenderWindow* window;
	Leaderboard leaderboard;
	bool leaderboard_window_is_open = false;
	class Buttons {
		private:
			sf::Sprite reset_button;
			sf::Sprite debug_button;
			sf::Sprite play_pause_button;
			sf::Sprite leaderboard_button;
			Game* game;
		public:
			Buttons(const Config* cfg, Game* game): game(game) {
				initialize_buttons(cfg);
			}
			void initialize_buttons(const Config* cf) {
				float cols = (float)cf->columns;
				float rows = (float)cf->rows;
				this->reset_button.setTexture(cf->textures.face_happy);
				this->reset_button.setPosition(
					sf::Vector2f((cols / 2.0f * 32) - 32, 
							32 * (rows + 0.5f)
					)
				);
				this->debug_button.setTexture(cf->textures.debug);
				this->debug_button.setPosition(
					sf::Vector2f(cols * 32 - 304,
						32 * (rows + 0.5f)
					)
				);
				this->play_pause_button.setTexture(cf->textures.pause);
				this->play_pause_button.setPosition(
					sf::Vector2f(cols * 32 - 240,
						32 * (rows + 0.5f)
					)
				);
				this->leaderboard_button.setTexture(cf->textures.leaderboard);
				this->leaderboard_button.setPosition(
					sf::Vector2f(cols * 32 - 176,
						32 * (rows + 0.5f)
					)
				);
			}
			void draw() const {
				this->game->window->draw(reset_button);
				this->game->window->draw(debug_button);
				this->game->window->draw(play_pause_button);
				this->game->window->draw(leaderboard_button);
			}
			bool clicked_reset_button(sf::Vector2i& mouse_coords) const {
				return (this->reset_button
						.getGlobalBounds()
						.contains((float)mouse_coords.x,
								  (float)mouse_coords.y));
			}
			bool handle_click(sf::Vector2i& mouse_coords) {
				if (this->reset_button
					.getGlobalBounds()
					.contains((float)mouse_coords.x,
							  (float)mouse_coords.y)) {
					this->game->reset();
				} else if (this->debug_button
					.getGlobalBounds()
					.contains((float)mouse_coords.x,
							  (float)mouse_coords.y)) {
					if (this->game->debug_mode) {
						std::cout << "Debug mode already on! Turning off...\n";
					} else {
						std::cout << "Debug mode off. Turning on!\n";
					}
					this->debug();
				} else if (this->leaderboard_button
					.getGlobalBounds()
					.contains((float)mouse_coords.x,
							  (float)mouse_coords.y)) {
					press_leaderboard_button();
				} else if (this->play_pause_button
					.getGlobalBounds()
					.contains((float)mouse_coords.x,
							  (float)mouse_coords.y)) {
					if (this->game->state == GAME_STATE::IN_PROGRESS) {
						this->pause();
					} else if (this->game->state == GAME_STATE::PAUSED) {
						this->play();
					} else {
						throw std::runtime_error("Loss / Win not handled.");
					}
				} else {
					return false;
				}
				return true;
			}
			void set_face_happy() {
				this->reset_button.setTexture(this->game->cfg->textures.face_happy);
			}
			void set_face_win() {
				this->reset_button.setTexture(this->game->cfg->textures.face_win);
			}
			void set_face_lose() {
				this->reset_button.setTexture(this->game->cfg->textures.face_lose);
			}
			void debug() {
				if (this->game->state == GAME_STATE::IN_PROGRESS ||
					this->game->state == GAME_STATE::PAUSED) {
					if (this->game->debug_mode) {
						this->game->debug_mode = false;
					} else {
						this->game->debug_mode = true;
					}
				}
				this->game->clear();
				this->game->draw();
			}
			void play() {
				this->game->state = GAME_STATE::IN_PROGRESS;
				this->game->ui_elements.resume_timer();
				this->play_pause_button.setTexture(this->game->cfg->textures.pause);
			}
			void pause() {
				this->game->state = GAME_STATE::PAUSED;
				this->game->ui_elements.pause_timer();
				this->play_pause_button.setTexture(this->game->cfg->textures.play);
			}
			void press_leaderboard_button() {
				this->game->leaderboard_window_is_open = true;
				std::cout << "Called \n";
			}
	};
	class UIElements { // handles mine counter and timer
		private:
			sf::Sprite digit;
			sf::Sprite timer;
			Game* game;
			double elapsed_duration;
			bool timer_is_paused = false;
			std::chrono::high_resolution_clock::time_point start;
		public:
			UIElements(Game* game): game(game), start(std::chrono::high_resolution_clock::now()) {};

			sf::IntRect get_rect_by_digit(int i) {
				return sf::IntRect(21 * i, 0, 21, 32);
			}
			void draw_digit(char c, int x_offset, bool is_mine_counter, bool is_minutes) {
				// handles digit drawing for mine-counter and time counter
				// "Is minutes" is specific to time counter.
				if (c == '-' && is_mine_counter) {
					// x offset not used in this conditional!
					this->digit.setTexture(this->game->cfg->textures.digits);
					this->digit.setTextureRect(get_rect_by_digit(10));
					this->digit.setPosition(
						sf::Vector2f(
							12, 32 * (static_cast<float>(this->game->cfg->rows) + 0.5f) + 16
						)
					);
					this->game->window->draw(this->digit);
				} else {
					int as_digit = c - '0';
					if (!(as_digit >= 0 && as_digit <= 9)) {
						throw std::runtime_error("Cannot parse digit that isn't between 0 and 9!");
					}
					this->digit.setTexture(this->game->cfg->textures.digits);
					this->digit.setTextureRect(get_rect_by_digit(as_digit));
					if (is_mine_counter) {
						this->digit.setPosition(
							sf::Vector2f(
								33 + 21 * static_cast<float>(x_offset), 
								32 * (static_cast<float>(this->game->cfg->rows) + 0.5f) + 16
							)
						);
					} else if (is_minutes) {
						this->digit.setPosition(
							sf::Vector2f(
								static_cast<float>(this->game->cfg->columns * 32) - 97 + 21 * static_cast<float>(x_offset),
								32 * (static_cast<float>(this->game->cfg->rows) + 0.5f) + 16
							)
						);
					} else if (!is_minutes) {
						// redundant but just to make sure
						this->digit.setPosition(
							sf::Vector2f(
								static_cast<float>(this->game->cfg->columns * 32) - 54 + 21 * static_cast<float>(x_offset),
								32 * (static_cast<float>(this->game->cfg->rows) + 0.5f) + 16
							)
						);
					}
					this->game->window->draw(this->digit);
				}
			}
			void draw_mine_counter() {
				int remaining_mines = game->get_remaining_mines();
				std::string mines_str = std::to_string(remaining_mines);
				int x_offset = 0;
				int abs_mines = std::abs(remaining_mines);
				if (abs_mines < 100) {
					this->draw_digit('0', x_offset++, true, false);
					if (abs_mines < 10) {
						this->draw_digit('0', x_offset++, true, false);
					}
				}
				if (remaining_mines < 0 && mines_str[0] == '-') {
					// since the position of a digit is index dependent, the negative gets counted in the calculation and offset is 1 higher than it should be (if it's a negative).
					x_offset--;
				}
				for (size_t i = 0; i < mines_str.size(); i++) {
					this->draw_digit(mines_str[i], static_cast<int>(i) + x_offset, true, false);
				}
			}
			
			void pause_timer() {
				// only works if game is about to pause or win is about to occur
				if (this->timer_is_paused) {
					return;
				}
				if (game->state != GAME_STATE::IN_PROGRESS || 
					this->game->leaderboard_window_is_open) {
					auto now = std::chrono::high_resolution_clock::now();
					this->elapsed_duration += std::chrono::duration<double>(now - this->start).count();
					this->timer_is_paused = true;
				} else {
					throw std::runtime_error("Cannot pause timer!");
				}
			}
			
			void resume_timer() {
				// only works if game is about to start
				if (this->game->state == GAME_STATE::IN_PROGRESS) {
					this->start = std::chrono::high_resolution_clock::now();
					this->timer_is_paused = false;
				} else {
					throw std::runtime_error("Cannot resume timer!");
				}
			}

			void reset_timer() {
				this->start = std::chrono::high_resolution_clock::now();
				this->elapsed_duration = 0;
				this->timer_is_paused = false;
			}
			
			double get_elapsed_seconds() {
				if (game->state == GAME_STATE::IN_PROGRESS) {
					auto now = std::chrono::high_resolution_clock::now();
					return this->elapsed_duration + std::chrono::duration<double>(now - this->start).count();
				} else {
					return this->elapsed_duration;
				}
			}
			
			int get_minutes_elapsed() {
				double secs = this->get_elapsed_seconds();
				if (secs < 60) {
					return 0;
				}
				return static_cast<int>(std::floor(secs / 60));
			}
			std::tuple<int, int> get_timer() {
				double secs = this->get_elapsed_seconds();
				int mins_elapsed = static_cast<int>(std::floor(secs / 60)); 
				int secs_elapsed = static_cast<int>(secs) % 60;
				return {mins_elapsed, secs_elapsed};
			}
			void draw_timer() {
				auto time = get_timer();
				int mins = std::get<0>(time);
				int secs = std::get<1>(time);
				std::string mins_str = std::to_string(mins);
				std::string secs_str = std::to_string(secs);
				int x_offset_mins = 0;
				int x_offset_secs = 0;
				if (mins < 10) {
					this->draw_digit('0', x_offset_mins++, false, true);
				}
				if (secs < 10) {
					this->draw_digit('0', x_offset_secs++, false, false);
				}
				for (size_t i = 0; i < mins_str.size(); i++) {
					this->draw_digit(mins_str[i], static_cast<int>(i) + x_offset_mins, false, true);
				}
				for (size_t i = 0; i < secs_str.size(); i++) {
					this->draw_digit(secs_str[i], static_cast<int>(i) + x_offset_secs, false, false);
				}
			}
			void draw() {
				this->draw_mine_counter();
				this->draw_timer();
			}

		};
	Buttons buttons;
	UIElements ui_elements;
	bool debug_mode = false;
public:
	Game(std::string name, Config* cfg, sf::RenderWindow* window):
		state(GAME_STATE::IN_PROGRESS),
		board(Board(cfg)),
		cfg(cfg),
		name(name),
		window(window),
		leaderboard(parse()),
		buttons(cfg, this),
		ui_elements(this)
	{};
	void draw_leaderboard_window() {
		const float width = (float)cfg->columns * 16;
		const float height = (float)cfg->rows * 16  + 50;
		sf::RenderWindow leaderboard_window(sf::VideoMode((int)width, (int)height), "Leaderboard", sf::Style::Close);
		sf::RectangleShape rect;
		sf::Font font;
		if (!font.loadFromFile("./files/font.ttf")) {
			throw std::runtime_error("Could not load font from file.");
		}
		rect.setSize(sf::Vector2f(width, height));
		rect.setFillColor(sf::Color::Blue);
		sf::Text leaderboard_text = new_text_object(
			font, "LEADERBOARD!", true,
			true, sf::Color::White, 20, 
			width / 2, height / 2 - 120
		);
		std::string leaderboard_str = get_leaderboard_str(&this->leaderboard);
		sf::Text leaderboard_str_text = new_text_object(
			font, leaderboard_str, true,
			false, sf::Color::White, 18,
			width / 2, height / 2 + 20);
		while (leaderboard_window.isOpen()) {
			sf::Event event;
			while (leaderboard_window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					leaderboard_window.close();
				} 
			}
			leaderboard_window.clear();
			leaderboard_window.draw(rect);
			leaderboard_window.draw(leaderboard_text);
			leaderboard_window.draw(leaderboard_str_text);
			leaderboard_window.display();
		}
		this->leaderboard_window_is_open = false;
	}
	void draw() {
		board.draw_sprites(this->window, this->debug_mode, this->state == GAME_STATE::PAUSED || this->leaderboard_window_is_open);
		buttons.draw();
		ui_elements.draw();
		if (this->leaderboard_window_is_open) { // trigger
			this->pause_timer();
			draw_leaderboard_window();
		}
	}
	void clear() {
		this->window->clear();
	}
	bool check_tile_press(sf::Vector2i& mouse_coords, bool left_click) {
		Tile* tile = this->board.get_clicked_tile(mouse_coords);
		if (tile == nullptr) {
			return false;
		}
		if (left_click && !tile->get_is_flagged()) {
			tile->reveal_tile();
		}
		if (!left_click) {
			if (tile->get_is_flagged()) {
				tile->set_flag_state(false);
			} else if (tile->get_is_hidden()){
				tile->set_flag_state(true);
			}
		} else {
			if (tile->get_is_flagged()) {
				return true;
			}
			if (tile->has_mine() && !tile->get_is_flagged()) {
				this->state = GAME_STATE::LOSS;
				this->handle_loss(mouse_coords);
			} else if (this->cfg->mines == this->board.count_hidden_tiles()){
				this->state = GAME_STATE::WIN;
				this->handle_win(mouse_coords);
			}
		}
		return true;
	}
	void handle_right_click(sf::Vector2i& mouse_coords) {
		if (this->state == GAME_STATE::IN_PROGRESS) {
			this->check_tile_press(mouse_coords, false);
		}
	}
	void handle_left_click(sf::Vector2i& mouse_coords) {
		switch (this->state) {
			case GAME_STATE::WIN:
				this->handle_win(mouse_coords);
				break;
			case GAME_STATE::LOSS:
				this->handle_loss(mouse_coords);
				break;
			case GAME_STATE::IN_PROGRESS:
				this->check_tile_press(mouse_coords, true);
				this->buttons.handle_click(mouse_coords);
				break;
			case GAME_STATE::PAUSED:
				this->buttons.handle_click(mouse_coords);
				break;
		}
	}
	void handle_click(sf::Vector2i& mouse_coords, bool left_click) {
		if (left_click) {
			handle_left_click(mouse_coords);
		} else {
			handle_right_click(mouse_coords);
		}
	}
	void start();
	void draw_mines() {
		auto mines = this->board.get_mines();
		auto iter = mines.begin();
		for (; iter != mines.end(); iter++) {
			(*iter)->reveal_tile();
		}
	}
	void handle_win(sf::Vector2i& mouse_coords) {
		if (this->buttons.clicked_reset_button(mouse_coords)) {
			this->state = GAME_STATE::IN_PROGRESS;
			this->buttons.set_face_happy();
			add_winner(name, static_cast<int>(this->ui_elements.get_elapsed_seconds()), &this->leaderboard);
			this->reset();
		} else {
			this->buttons.set_face_win();
			this->pause_timer();
		}
	}
	void handle_loss(sf::Vector2i& mouse_coords) {
		if (this->buttons.clicked_reset_button(mouse_coords)) {
			this->state = GAME_STATE::IN_PROGRESS;
			this->buttons.set_face_happy();
			this->reset();
			set_no_new_player_replaced(&this->leaderboard);
		} else {
			this->draw_mines();
			this->buttons.set_face_lose();
			this->pause_timer();
		}
	}
	int get_remaining_mines() {
		return this->cfg->mines - this->board.count_flagged_tiles();
	}
	void pause_timer() {
		this->ui_elements.pause_timer();
	}
	void resume_timer() {
		this->ui_elements.resume_timer();
	}
	void reset() {
		this->ui_elements.reset_timer();
		this->window->clear();
		this->board.reset();
	}
	GAME_STATE get_state() {
		return this->state;
	}
};
