#include "../../include/Utils/Coord.h"

Coord& Coord::operator+=(const Coord& other) {
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Coord& Coord::operator-=(const Coord& other) {
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Coord operator-(Coord c1, Coord c2) {
	return c1 -= c2;
}

Coord operator+(Coord c1, Coord c2) {
	return c1 += c2;
}
