#pragma once
#include <random>
#include "../Base/BaseApp.h"
#include "../Game/Figure.h"

enum class Comand {
	none,
	move_right,
	move_left,
	move_down,
	rotate
};

class Tetris : public BaseApp
{
private:
	typedef BaseApp Parent;

	// 
	// constants for different tasks 
	// 
	const double default_time{ 0.5 };
	const double accelerated_time{ 0.05 };
	const int field_width{ 15 }; 
	const int field_height{ 20 };
	const Coord field_start_coord{ 1,1 }; 
	const Coord figure_start_coord{ 6,0 };
	const Coord f_figure_pos{ 19,2 };
	// poses used to clear old future figure
	const std::vector<Coord> next_figure_poses {
		{19, 5},
		{19, 4},
		{19, 3},
		{19, 2},

		{20, 5},
		{20, 4},
		{20, 3},
		{20, 2},

		{21, 5},
		{21, 4},
		{21, 3},
		{21, 2},
	};

	Coord figure_coord{ figure_start_coord };

	Figure curr_figure;
	Figure next_figure;

	std::vector<std::vector<bool>> occupied_coords;
	std::vector<Coord> old_poses;
	int score{};

	Comand curr_comand{ Comand::none };

	double curr_time_sum{ 0 };
	double delta_time_down{ 0.5 };

	// Sets needed console font and sizes
	void set_console_characteristics();

	inline void rotate(); 
	inline void move_right();
	inline void move_left();
	// checks if figure position is within field borders and 
	// on unoccupied position
	inline bool is_correct_figure_pos();
	// checks comand and makes appropriate action
	void process_comand(); 

	// attaches figure to occupied poses
	void attach_figure();
	// tries to lower current figure down and if it could be pushed lower pushes.
	// returns true if figure pushed down successfully
	bool process_lowering_down();
	// function to change current figure to future figure and future figure to another.
	// Returns true if new figure can be placed (there is a free space)
	bool try_refresh_figure();  
							   
	// clears old figure position
	void clear_old_pos(); 
	// draws figure in current position
	void draw_cur_figure(); 
	// draws next figure in right upper corner
 	void draw_next_figure();
	// draws dots in inoccupied poses and 'char to draw' in occupied poses
	void draw_field(); 
	// draws borders of every ui component: like field borders, left section with future figure borders etc
	void draw_hud(); 
	// draws numbers after the "Score" word on hud
	void draw_score(); 

	// checks if player has some full lines and destroys them, also adds player score
	void check_lines();

	// checks if player pressed down arrow
	bool go_down{ false };

	const wchar_t char_to_draw_figure = 10;
	const wchar_t char_to_draw_emptiness = '.';
	const wchar_t char_to_draw_borders = '#';
public:
	Tetris();
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);
	
};
