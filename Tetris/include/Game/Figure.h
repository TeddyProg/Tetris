#pragma once
#include <vector>
#include "../Utils/Coord.h"

enum class FigureType {
	T,
	I,
	L,
	J,
	O,
	Z,
	S
};


class Figure {
public:
	void rotate_clockwise();
	void rotate_counterclockwise();

	Figure(const std::vector<Coord>& uposes);

	Figure() = default;

	std::vector<Coord>& get_poses();
private:
	std::vector<Coord> unit_positions;
};


template <FigureType type>
Figure getFigure();


