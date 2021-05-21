#include "../../include/Game/Figure.h"
#include <iostream>




Figure::Figure(const std::vector<Coord>& coords):
	unit_positions{ coords }{

}



template <>
Figure getFigure<FigureType::T>() {
	Figure figure {
		{
		{ 1, 0 },
		{ 0, 1 },
		{ 1, 1 },
		{ 2, 1 },
		}
	};
	return figure;
}

template <>
Figure getFigure<FigureType::O>() {
	Figure figure{
		{
		{ 0, 0 },
		{ 1, 0 },
		{ 0, 1 },
		{ 1, 1 },
		}
	};
	return figure;
}


template <>
Figure getFigure<FigureType::Z>() {
	Figure figure{
		{
		{ 0,  0 },
		{ 1,  0 },
		{ 1,  1 },
		{ 2,  1 },
		}
	};
	return figure;
}

template <>
Figure getFigure<FigureType::S>() {
	Figure figure{
		{
		{ 0, 1 },
		{ 1, 0 },
		{ 1, 1 },
		{ 2, 0 },
		}
	};
	return figure;
}


template <>
Figure getFigure<FigureType::I>() {
	Figure figure{
		{
		{ 1, 0 },
		{ 1, 1 },
		{ 1, 2 },
		{ 1, 3 },
		}
	};
	return figure;
}

template <>
Figure getFigure<FigureType::J>() {
	Figure figure{
		{
		{ 1, 0 },
		{ 1, 1 },
		{ 1, 2 },
		{ 0, 2 },
		}
	};
	return figure;
}


template <>
Figure getFigure<FigureType::L>() {
	Figure figure{
		{
		{ 1, 0 },
		{ 1, 1 },
		{ 1, 2 },
		{ 2, 2 },
		}
	};
	return figure;
}

std::vector<Coord>& Figure::get_poses() {
	return unit_positions;
}

void Figure::rotate_clockwise() {
	Coord delta{ 1,1 };


	for (Coord& pos : unit_positions) {
		Coord old_p{ pos - delta };
		pos.x =  -1 * old_p.y;
		pos.y = 1 * old_p.x;
		pos += delta;
	}
}

void Figure::rotate_counterclockwise() {
	Coord delta{ 1,1 };

	for (Coord& pos : unit_positions) {
		Coord old_p{ pos - delta };
		pos.x = 1 * old_p.y;
		pos.y = -1 * old_p.x;
		pos += delta;
	}

}
