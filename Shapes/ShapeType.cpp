#include "ShapeType.h"

std::string ShapeToString(ShapeType shape)
{
	switch (shape)
	{
	case ShapeType::LineSegment:
		return "LineSegment";
	case ShapeType::Triangle:
		return "Triangle";
	case ShapeType::Rectangle:
		return "Rectangle";
	case ShapeType::Circle:
		return "Circle";
	default:
		throw std::runtime_error("Unknown shape");
	}
}