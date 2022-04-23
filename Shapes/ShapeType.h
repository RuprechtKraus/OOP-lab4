#pragma once
#include <stdexcept>
#include <string>

enum class ShapeType
{
	LineSegment,
	Triangle,
	Rectangle,
	Circle
};

std::string ShapeToString(ShapeType shape);