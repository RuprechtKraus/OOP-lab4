#pragma once
#include "ISolidShape.h"
#include "Point.h"

class Triangle final : public ISolidShape
{
public:
	Triangle(Point v1, Point v2, Point v3, uint32_t fillColor = 0xFFFFFFU, std::optional<uint32_t> outlineColor = std::nullopt);

	double GetArea() const override;
	double GetPerimeter() const override;
	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;

private:
	void CalculateEdges();

	Point m_vertex1{};
	Point m_vertex2{};
	Point m_vertex3{};
	double m_edgeA{};
	double m_edgeB{};
	double m_edgeC{};
};