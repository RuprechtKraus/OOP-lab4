#include "Triangle.h"
#include <cmath>
#include <iostream>
#include <sstream>

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, 
	std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor)
	: ISolidShape(ShapeType::Triangle, fillColor, outlineColor)
	, m_vertex1(v1)
	, m_vertex2(v2)
	, m_vertex3(v3)
{
	UpdateEdges();
}

void Triangle::UpdateEdges()
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

double Triangle::GetEdgeA() const
{
	return m_edgeA;
}

double Triangle::GetEdgeB() const
{
	return m_edgeB;
}

double Triangle::GetEdgeC() const
{
	return m_edgeC;
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

void Triangle::Draw(ICanvas& canvas) const
{
	std::vector<Point> points{ m_vertex1, m_vertex2, m_vertex3 };
	canvas.DrawPolygon(points, m_fillColor, m_outlineColor);
}

std::string Triangle::ToString() const
{
	std::ostringstream ss;

	PrepareStream(ss);
	ss << ISolidShape::ToString()
	   << "\nVertex 1: " << m_vertex1.x << ", " << m_vertex1.y
	   << "\nVertex 2: " << m_vertex2.x << ", " << m_vertex2.y
	   << "\nVertex 3: " << m_vertex3.x << ", " << m_vertex3.y
	   << "\nEdge A length: " << m_edgeA
	   << "\nEdge B length: " << m_edgeB
	   << "\nEdge C length: " << m_edgeC
	   << std::endl;
	ResetStream(ss);

	return ss.str();
}