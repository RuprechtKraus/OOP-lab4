#pragma once
#include "ISolidShape.h"
#include "Shape.h"

class SolidShape : public ISolidShape, public Shape
{
public:
	SolidShape(ShapeType type, 
		std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor);

	std::optional<uint32_t> GetFillColor() const override;
	std::optional<uint32_t> GetOutlineColor() const override;
	std::string ToString() const override;

protected:
	std::optional<uint32_t> m_fillColor{};
};
