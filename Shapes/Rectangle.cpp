#include "Rectangle.h"
#include <sstream>

Rectangle::Rectangle(const Point& topLeft, const Point& bottomRight,
	std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor)
	: SolidShape(ShapeType::Rectangle, fillColor, outlineColor)
{
	if (bottomRight.x < topLeft.x || bottomRight.y < topLeft.y)
	{
		throw std::invalid_argument("Incorrect bottom right vertex positioning");
	}

	m_topLeft = topLeft;
	m_bottomRight = bottomRight;
	UpdateDimensions();
}

void Rectangle::UpdateDimensions()
{
	m_width = m_bottomRight.x - m_topLeft.x;
	m_height = m_bottomRight.y - m_topLeft.y;
}

double Rectangle::GetArea() const
{
	return m_width * m_height;
}

double Rectangle::GetPerimeter() const
{
	return (m_width + m_height) * 2;
}

double Rectangle::GetWidth() const
{
	return m_width;
}

double Rectangle::GetHeight() const
{
	return m_height;
}

Point Rectangle::GetTopLeft() const
{
	return m_topLeft;
}

Point Rectangle::GetBottomRight() const
{
	return m_bottomRight;
}

void Rectangle::Draw(ICanvas& canvas) const
{
	std::vector<Point> points{
		m_topLeft,
		{ m_topLeft.x + m_width, m_topLeft.y },
		m_bottomRight,
		{ m_topLeft.x, m_topLeft.y + m_height }
	};
	canvas.DrawPolygon(points, m_fillColor, m_outlineColor);
}

std::string Rectangle::ToString() const
{
	std::ostringstream ss;

	PrepareStream(ss);
	ss << SolidShape::ToString()
	   << "\nTop left: " << m_topLeft.x << ", " << m_topLeft.y
	   << "\nBottom right: " << m_bottomRight.x << ", " << m_bottomRight.y
	   << "\nWidth: " << m_width
	   << "\nHeight: " << m_height
	   << std::endl;
	ResetStream(ss);

	return ss.str();
}