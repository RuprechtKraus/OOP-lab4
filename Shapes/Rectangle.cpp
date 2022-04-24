#include "Rectangle.h"

Rectangle::Rectangle(const Point& topLeft, const Point& bottomRight,
	uint32_t fillColor, std::optional<uint32_t> outlineColor)
	: ISolidShape(ShapeType::Rectangle, fillColor, outlineColor)
{
	if (bottomRight.x < topLeft.x || bottomRight.y > topLeft.y)
	{
		throw std::runtime_error("Incorrect bottom right vertex positioning");
	}

	m_topLeft = topLeft;
	m_bottomRight = bottomRight;
}

double Rectangle::GetArea() const
{
	return 0.0;
}

double Rectangle::GetPerimeter() const
{
	return 0.0;
}

double Rectangle::GetWidth() const
{
	return 0.0;
}

double Rectangle::GetHeight() const
{
	return 0.0;
}

Point Rectangle::GetTopLeft() const
{
	return m_topLeft;
}

Point Rectangle::GetBottomRight() const
{
	return m_bottomRight;
}

std::string Rectangle::ToString() const
{
	return "";
}