#pragma once
#include "ShapeType.h"
#include <optional>
#include <string>

class IShape
{
public:
	IShape(ShapeType type, std::optional<uint32_t> outlineColor);
	virtual ~IShape();

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	std::string ToString() const;
	std::optional<uint32_t> GetOutlineColor() const;

private:
	ShapeType m_shape{};
	std::optional<uint32_t> m_outlineColor{};
};