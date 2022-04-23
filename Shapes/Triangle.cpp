#include "Triangle.h"
#include <cmath>

Triangle::Triangle(Point v1, Point v2, Point v3, uint32_t fillColor, std::optional<uint32_t> outlineColor)
	: ISolidShape(ShapeType::Triangle, fillColor, outlineColor)
	, m_vertex1(v1)
	, m_vertex2(v2)
	, m_vertex3(v3)
{
	CalculateEdges();
}

void Triangle::CalculateEdges()
{
	m_edgeA = Distance(m_vertex1, m_vertex2);
	m_edgeB = Distance(m_vertex1, m_vertex3);
	m_edgeC = Distance(m_vertex2, m_vertex3);
}

double Triangle::GetArea() const
{
	double p = (m_edgeA + m_edgeB + m_edgeC) * 0.5;
	return std::sqrt(p * (p - m_edgeA) * (p - m_edgeB) * (p - m_edgeC));
}

double Triangle::GetPerimeter() const
{
	return m_edgeA + m_edgeB + m_edgeC;
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
