#pragma once
#include "IShape.h"
#include "Point.h"

class LineSegment final : public IShape
{
public:
	LineSegment(Point start, Point end, uint32_t color = 0x000000U);

	double GetArea() const override;
	double GetPerimeter() const override;
	double GetLength() const;
	uint32_t GetColor() const;
	Point GetStartPoint() const;
	Point GetEndPoint() const;

private:
	void AppendProperties(std::ostream& os) const override;

	Point m_start{};
	Point m_end{};
	uint32_t m_color{};
};
