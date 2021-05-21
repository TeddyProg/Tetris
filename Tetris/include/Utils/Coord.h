#pragma once
struct Coord {
	int x;
	int y;

	Coord& operator+=(const Coord&);
	Coord& operator-=(const Coord&);
};

Coord operator+(Coord c1, Coord c2);
Coord operator-(Coord c1, Coord c2);