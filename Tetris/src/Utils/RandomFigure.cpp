#include "../../include/Utils/RandomFigure.h"
#include <random>
#include <chrono>
#include <stdexcept>


Figure getRandomFigure() {
	static std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	static std::uniform_int_distribution<int> dist{ 0, 6 };

	FigureType ftype = static_cast<FigureType>(dist(generator));

	switch (ftype)
	{
	case FigureType::T:
		return getFigure<FigureType::T>();
	case FigureType::I:
		return getFigure<FigureType::I>();
	case FigureType::L:
		return getFigure<FigureType::L>();
	case FigureType::J:
		return getFigure<FigureType::J>();
	case FigureType::O:
		return getFigure<FigureType::O>();
	case FigureType::Z:
		return getFigure<FigureType::Z>();
	case FigureType::S:
		return getFigure<FigureType::S>();
	default:
		throw std::runtime_error("Unimplemented figure type");
		break;
	}

}
