#include "ISolidShape.h"
#include <iomanip>
#include <sstream>

ISolidShape::ISolidShape(ShapeType type, std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor)
	: IShape(type, outlineColor)
	, m_fillColor(fillColor)
{
}

std::string ISolidShape::ToString() const
{
	std::ostringstream ss;
	double a = GetArea();
	PrepareStream(ss);
	ss << IShape::ToString()
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

std::optional<uint32_t> ISolidShape::GetFillColor() const
{
	return m_fillColor;
}