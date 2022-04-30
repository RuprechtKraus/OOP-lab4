#pragma once
#include "ICanvas.h"
#include "IShape.h"
#include "Point.h"

class LineSegment final : public IShape
{
public:
	LineSegment(const Point& start, const Point& end, uint32_t color = 0x000000U);

	double GetArea() const override;
	double GetPerimeter() const override;
	double GetLength() const;
	uint32_t GetColor() const;
	Point GetStartPoint() const;
	Point GetEndPoint() const;
	std::string ToString() const override;
	void Draw(ICanvas& canvas) const override;

private:
	Point m_start{};
	Point m_end{};
	uint32_t m_color{};
};
