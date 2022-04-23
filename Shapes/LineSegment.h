#pragma once
#include "IShape.h"
#include "Point.h"

class LineSegment final : public IShape
{
public:
	LineSegment(Point start, Point end, std::optional<uint32_t> outlineColor = std::nullopt);

	double GetArea() const override;
	double GetPerimeter() const override;
	double GetLength() const;
	Point GetStartPoint() const;
	Point GetEndPoint() const;

private:
	Point m_start{};
	Point m_end{};
};
