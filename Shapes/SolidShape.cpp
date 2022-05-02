#include "SolidShape.h"
#include <sstream>

SolidShape::SolidShape(ShapeType type, std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor)
	: Shape(type, outlineColor)
	, m_fillColor(fillColor)
{
}

std::string SolidShape::ToString() const
{
	std::ostringstream ss;
	double a = GetArea();
	PrepareStream(ss);
	ss << Shape::ToString()
	   << "\nArea: " << GetArea()
	   << "\nPerimeter: " << GetPerimeter();
	if (m_fillColor)
	{
		ss << "\nFill color: " << m_fillColor.value();
	}
	if (m_outlineColor)
	{
		ss << "\nOutline color: " << m_outlineColor.value();
	}
	ResetStream(ss);

	return ss.str();
};

std::optional<uint32_t> SolidShape::GetFillColor() const
{
	return m_fillColor;
}

std::optional<uint32_t> SolidShape::GetOutlineColor() const
{
	return Shape::GetOutlineColor();
}