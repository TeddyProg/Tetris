// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "../../include/Game/TetrisGame.h"
#include <vector>
#include <algorithm>
#include <windows.h>
#include "../../include/Utils/RandomFigure.h"


Tetris::Tetris() : 
	Parent(24, 25), 
	occupied_coords{ field_height,std::vector<bool>(field_width, false) },
	curr_figure (getRandomFigure()),
	next_figure(getRandomFigure()) {

	set_console_characteristics();
	draw_hud();
	draw_next_figure();
	draw_score();
}

void Tetris::draw_hud() {
	for (int x = 0; x <= X_SIZE; ++x) {
		SetChar(x, 0, char_to_draw_borders);
		SetChar(x, Y_SIZE, char_to_draw_borders);
		SetChar(x, Y_SIZE - 4, char_to_draw_borders);
	}
	for (int y = 0; y <= Y_SIZE; ++y) {
		SetChar(0, y, char_to_draw_borders);
		SetChar(X_SIZE, y, char_to_draw_borders);

		if (Y_SIZE - y > 4) SetChar(X_SIZE - 8, y, char_to_draw_borders);
	}
	for (int x = 1; x < X_SIZE - 8; ++x) {
		for (int y = 1; y < Y_SIZE - 4; ++y) {
			SetChar(x, y, char_to_draw_emptiness);
		}
	}

	char word[] = "> Score: ";
	for (int x = 3; x - 3 < sizeof(word) / sizeof(char); ++x) {
		SetChar(x, Y_SIZE - 2, (int)word[x - 3]);
	}
}

void Tetris::KeyPressed(int btnCode)
{
	static bool arrowClicked{ false }; // variable to detect whether arrow was clicked for function getch();

	switch (btnCode) {
	case 77: // right arrow
		if (arrowClicked) {
			curr_comand = Comand::move_right;
			arrowClicked = false;
		}
		break;
	case 75: // left arrow
		if (arrowClicked) {
			curr_comand = Comand::move_left;
			arrowClicked = false;
		}
		break;
	case 80:// down arrow
		if (arrowClicked) {
			curr_comand = Comand::move_down;
			arrowClicked = false;
		}
		break;
	case ' ':
		curr_comand = Comand::rotate;
		break;
	case 224:
		arrowClicked = true;
	}

}

void Tetris::draw_score() {

	std::string s = std::to_string(score);
	for (int x = 12; x - 12 < s.size(); ++x) {
		SetChar(x, Y_SIZE - 2, s[x-12]);
	}
}

void Tetris::UpdateF(float deltaTime)
{
	curr_time_sum += deltaTime;
	set_console_characteristics(); // using this function here to not allow user to change console characteristics while playing
	process_comand();

	if (!process_lowering_down()) { // if its time to lower figure and it cant be lowered more 

		attach_figure();
		
		if (!try_refresh_figure()) { // if it is impossible to suumon new figure because places for it is occupied
			exit(0); 
		}

		check_lines();
		draw_field();
		draw_score();
		draw_next_figure();
		curr_comand = Comand::none;
	}
	else {
		clear_old_pos(); // old positions becomes part of occupied field
	}
	
	draw_cur_figure();
}

void Tetris::draw_field() {
	for (int x = 0; x < occupied_coords[0].size(); ++x) {
		for (int y = 0; y < occupied_coords.size(); ++y) {
			Coord coord{ x,y };
			coord += field_start_coord;
			if (occupied_coords[y][x]) {
				SetChar(coord.x, coord.y, char_to_draw_figure); //char_to_draw_figure
			}
			else {
				SetChar(coord.x, coord.y, char_to_draw_emptiness); //char_to_draw_figure
			}
		}
	}
}


void Tetris::process_comand() {
	if (!go_down) {
		switch (curr_comand)
		{
		case Comand::none:
			break;
		case Comand::move_right:
			move_right();
			break;
		case Comand::move_left:
			move_left();
			break;
		case Comand::rotate:
			rotate();
			break;
		case Comand::move_down:
			delta_time_down = accelerated_time;
			go_down = true;
			break;
		default:
			break;
		}
		curr_comand = Comand::none;
	}
}


void Tetris::check_lines() {
	auto it = std::remove_if(occupied_coords.begin(), occupied_coords.end(),
		[](const std::vector<bool>& vec) {
			for (bool val : vec) {
				if (!val) return false;
			}
			return true;
		});

	int num_lines = occupied_coords.end() - it;
	occupied_coords.erase(it, occupied_coords.end());
	score += num_lines * 100;
	occupied_coords.insert(occupied_coords.begin(), num_lines, std::vector<bool>(field_width));
}


void Tetris::draw_next_figure() {
	std::vector<Coord> poses{ next_figure.get_poses() };
	for (Coord pos : next_figure_poses) {
		SetChar(pos.x, pos.y, ' ');
	}

	for (Coord pos : poses) {
		pos += f_figure_pos;
		SetChar(pos.x, pos.y, char_to_draw_figure);
	}
}


void Tetris::rotate() {
	curr_figure.rotate_clockwise();
	if (!is_correct_figure_pos()) 
		curr_figure.rotate_counterclockwise();
}

void Tetris::move_right() {
	figure_coord.x++;
	if (!is_correct_figure_pos()) 
		figure_coord.x--;
}

void Tetris::move_left() {
	figure_coord.x--;
	if (!is_correct_figure_pos()) 
		figure_coord.x++;
	
}   

bool Tetris::process_lowering_down() {
	if (curr_time_sum >= delta_time_down) {
		curr_time_sum = 0;
		figure_coord.y++;
		for (Coord c : curr_figure.get_poses()) {
			c += figure_coord;
			if (c.y >= field_height || occupied_coords[c.y][c.x]) {
				figure_coord.y--;
				return false;
			}
		}
	}

	return true;
}

void Tetris::clear_old_pos() {
	for (const auto& coord : old_poses) {
		SetChar(coord.x, coord.y, char_to_draw_emptiness);
	}
}

void Tetris::draw_cur_figure() {
	std::vector<Coord> poses{ curr_figure.get_poses() };
	for (Coord& pos : poses) {
		pos += figure_coord;
		pos += field_start_coord;
		SetChar(pos.x, pos.y, char_to_draw_figure); //char_to_draw_figure

	}
	old_poses = std::move(poses);

}

bool Tetris::try_refresh_figure() {
	figure_coord = figure_start_coord;
	for (Coord c : next_figure.get_poses()) {
		c += figure_coord;
		if (occupied_coords[c.y][c.x]) {
			return false;
		}
	}
	curr_figure = next_figure;
	next_figure = getRandomFigure();
	
}

void Tetris::attach_figure() {
	if (go_down) {
		delta_time_down = default_time;
		go_down = false;
	}

	for (Coord pos : curr_figure.get_poses()) {
		pos += figure_coord;
		occupied_coords[pos.y][pos.x] = true;
	}
}

void Tetris::set_console_characteristics() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX font_info{ sizeof(CONSOLE_FONT_INFOEX) };

	if (!GetCurrentConsoleFontEx(console, TRUE, &font_info)) {
		std::cout << "GetCurrentConsoleFontEx failed with error " << GetLastError() << std::endl;
		exit(-1);
	}

	wcscpy_s(font_info.FaceName, L"Terminal");

	font_info.dwFontSize.X = 8;
	font_info.dwFontSize.Y = 12;

	if (!SetCurrentConsoleFontEx(console, TRUE, &font_info)) {
		std::cout << "SetCurrentConsoleFontEx failed with error " << GetLastError() << std::endl;
		exit(-1);
	}
}

bool Tetris::is_correct_figure_pos() {
	for (Coord coord : curr_figure.get_poses()) {
		coord += figure_coord;
		if ((coord.x < 0 || coord.x >= field_width) || occupied_coords[coord.y][coord.x]) {
			return false;
		}
	}
	return true;
}