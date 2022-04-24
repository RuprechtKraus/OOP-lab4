#include "Circle.h"
#include <cmath>
#include <numbers>
#include <sstream>

Circle::Circle(const Point& center, double radius,
	uint32_t fillColor, std::optional<uint32_t> outlineColor)
	: ISolidShape(ShapeType::Circle, fillColor, outlineColor)
	, m_center(center)
{
	if (radius < 0)
	{
		throw std::invalid_argument("Negative radius");
	}

	m_radius = radius;
}

double Circle::GetArea() const
{
	return std::numbers::pi * std::pow(m_radius, 2);
}

double Circle::GetPerimeter() const
{
	return 2 * std::numbers::pi * m_radius;
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
	std::ostringstream ss;

	PrepareStream(ss);
	ss << ISolidShape::ToString()
	   << "\nCenter: " << m_center.x << ", " << m_center.y
	   << "\nRadius: " << m_radius
	   << std::endl;
	ResetStream(ss);

	return ss.str();
}