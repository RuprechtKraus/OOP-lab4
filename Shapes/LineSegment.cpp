#include "LineSegment.h"

LineSegment::LineSegment(Point start, Point end, std::optional<uint32_t> outlineColor)
	: IShape(ShapeType::LineSegment, outlineColor)
	, m_start(start)
	, m_end(end)
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

Point LineSegment::GetStartPoint() const
{
	return m_start;
}

Point LineSegment::GetEndPoint() const
{
	return m_end;
}