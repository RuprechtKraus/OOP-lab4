#include "Triangle.h"

Triangle::Triangle(Point v1, Point v2, Point v3, uint32_t fillColor, std::optional<uint32_t> outlineColor)
	: ISolidShape(ShapeType::Triangle, fillColor, outlineColor)
	, m_vertex1(v1)
	, m_vertex2(v2)
	, m_vertex3(v3)
{
}

double Triangle::GetArea() const
{
	return 0.0;
}

double Triangle::GetPerimeter() const
{
	return 0.0;
}

Point Triangle::GetVertex1() const
{
	return m_vertex1;
}

Point Triangle::GetVertex2() const
{
	return m_vertex2;
}

Point Triangle::GetVertex3() const
{
	return m_vertex3;
}
