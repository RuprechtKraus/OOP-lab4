#include "Circle.h"

Circle::Circle(const Point& center, double radius,
	uint32_t fillColor, std::optional<uint32_t> outlineColor)
	: ISolidShape(ShapeType::Circle, fillColor, outlineColor)
	, m_center(center)
	, m_radius(radius)
{
}

double Circle::GetArea() const
{
	return 0.0;
}

double Circle::GetPerimeter() const
{
	return 0.0;
}

double Circle::GetRadius() const
{
	return m_radius;
}

Point Circle::GetCenter() const
{
	return m_center;
}

std::string Circle::ToString() const
{
	return "";
}