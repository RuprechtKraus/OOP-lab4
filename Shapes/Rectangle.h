#pragma once
#include "ISolidShape.h"
#include "Point.h"

class Rectangle final : public ISolidShape
{
public:
	Rectangle(const Point& topLeft, const Point& bottomRight, 
		uint32_t fillColor = 0xFFFFFFU, std::optional<uint32_t> outlineColor = std::nullopt);

	double GetArea() const override;
	double GetPerimeter() const override;
	double GetWidth() const;
	double GetHeight() const;
	Point GetTopLeft() const;
	Point GetBottomRight() const;
	std::string ToString() const override;

private:
	Point m_topLeft{};
	Point m_bottomRight{};
};