#include "LineSegment.h"
#include <iomanip>
#include <iostream>
#include <sstream>

LineSegment::LineSegment(const Point& start, const Point& end, uint32_t color)
	: IShape(ShapeType::LineSegment, std::nullopt)
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

uint32_t LineSegment::GetColor() const
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

std::string LineSegment::ToString() const
{
	std::ostringstream ss;

	PrepareStream(ss);
	ss << IShape::ToString()
	   << "\nColor: " << m_color
	   << "\nStart: " << m_start.x << ", " << m_start.y
	   << "\nEnd: " << m_end.x << ", " << m_end.y
	   << "\nLength: " << GetLength()
	   << std::endl;
	ResetStream(ss);

	return ss.str();
}