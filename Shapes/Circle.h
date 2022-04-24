#pragma once
#include "ISolidShape.h"
#include "Point.h"

class Circle final : public ISolidShape
{
public:
	Circle(const Point& center, double radius, 
		uint32_t fillColor = 0xFFFFFFU, std::optional<uint32_t> outlineColor = std::nullopt);

	double GetArea() const override;
	double GetPerimeter() const override;
	double GetRadius() const;
	Point GetCenter() const;
	std::string ToString() const override;

private:
	Point m_center{};
	double m_radius{};
};