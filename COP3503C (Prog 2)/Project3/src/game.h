#pragma once
#include "board.h"
#include "config.h"
#include "tile.h"

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
			void draw(sf::RenderWindow* _window) const {
				_window->draw(reset_button);
				_window->draw(debug_button);
				_window->draw(play_pause_button);
				_window->draw(leaderboard_button);
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
					std::cout << "Clicked!\n";
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
				this->play_pause_button.setTexture(this->game->cfg->textures.pause);
			}
			void pause() {
				this->game->state = GAME_STATE::PAUSED;
				this->play_pause_button.setTexture(this->game->cfg->textures.play);
			}
			void press_leaderboard_button() {

			}
	};
	class UIElements {
		private:
			sf::Sprite counter;
			sf::Sprite timer;
		public:
			UIElements(const Config* cfg) {
				initialize_sprites(cfg);
			}
			void initialize_sprites(const Config* cfg) {

			}
			bool handle_click(sf::Vector2i& mouse_coords) {
				return false;
			}
			void start_timer();
	};
	Buttons buttons;
	UIElements ui_elements;
	bool debug_mode = false;
public:
	Game(Config* cfg, sf::RenderWindow* window):
		state(GAME_STATE::IN_PROGRESS),
		board(Board(cfg)),
		cfg(cfg),
		window(window),
		buttons(cfg, this),
		ui_elements(cfg)
	{};
	void draw() {
		board.draw_sprites(this->window, this->debug_mode);
		buttons.draw(this->window);
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
				this->ui_elements.handle_click(mouse_coords);
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
			this->reset();
		} else {
			this->buttons.set_face_win();
		}
	}
	void handle_loss(sf::Vector2i& mouse_coords) {
		if (this->buttons.clicked_reset_button(mouse_coords)) {
			this->state = GAME_STATE::IN_PROGRESS;
			this->buttons.set_face_happy();
			this->reset();
		} else {
			this->draw_mines();
			this->buttons.set_face_lose();
		}
	}
	void pause();
	void reset() {
		this->window->clear();
		this->board.reset();
	}
	GAME_STATE get_state() {
		return this->state;
	}
};
