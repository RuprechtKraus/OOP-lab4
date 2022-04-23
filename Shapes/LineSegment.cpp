#include "LineSegment.h"

LineSegment::LineSegment(Point start, Point end, uint32_t color, std::optional<uint32_t> outlineColor)
	: IShape(ShapeType::LineSegment, outlineColor)
	, m_start(start)
	, m_end(end)
	, m_color(color)
{
}

double LineSegment::GetArea() const
{
	return Distance(m_start, m_end);
}

double LineSegment::GetLength() const
{
	return GetArea();
}

double LineSegment::GetPerimeter() const
{
	return 0.0;
}

uint16_t LineSegment::GetColor() const
{
	return m_color;
}

Point LineSegment::GetStartPoint() const
{
	return m_start;
}

Point LineSegment::GetEndPoint() const
{
	return m_end;
}