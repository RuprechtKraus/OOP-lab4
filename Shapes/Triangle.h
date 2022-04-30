#pragma once
#include "ISolidShape.h"
#include "Point.h"

class Triangle final : public ISolidShape
{
public:
	Triangle(const Point& v1, const Point& v2, const Point& v3, 
		std::optional<uint32_t> fillColor = 0xFFFFFFU, std::optional<uint32_t> outlineColor = std::nullopt);

	double GetArea() const override;
	double GetPerimeter() const override;
	double GetEdgeA() const;
	double GetEdgeB() const;
	double GetEdgeC() const;
	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;
	void Draw(ICanvas& canvas) const override;
	std::string ToString() const override;

private:
	void UpdateEdges();

	Point m_vertex1{};
	Point m_vertex2{};
	Point m_vertex3{};
	double m_edgeA{};
	double m_edgeB{};
	double m_edgeC{};
};