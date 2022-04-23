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
	virtual std::string ToString() const;
	std::optional<uint32_t> GetOutlineColor() const;

protected:
	ShapeType m_shape{};
	std::optional<uint32_t> m_outlineColor{};

private:
	virtual void AppendProperties(std::ostream& os) const = 0;
};