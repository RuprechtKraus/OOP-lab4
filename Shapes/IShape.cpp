#include "IShape.h"
#include <sstream>

IShape::IShape(ShapeType type, std::optional<uint32_t> outlineColor)
	: m_shape(type)
	, m_outlineColor(outlineColor)
{
}

IShape::~IShape()
{
}

std::string IShape::ToString() const
{
	std::ostringstream ss;
	ss.precision(1);
	ss << std::fixed << std::hex << std::uppercase << std::showbase;
	ss << "Type: " << ShapeToString(m_shape)
	   << "\nArea: " << GetArea()
	   << "\nPerimeter: " << GetPerimeter();
	if (m_outlineColor.has_value())
	{
		ss << "\nOutline: " << m_outlineColor.value();
	}
	AppendProperties(ss);
	ss << std::dec << std::nouppercase << std::noshowbase;
	ss.precision(6);
	return ss.str();
}

std::optional<uint32_t> IShape::GetOutlineColor() const
{
	return m_outlineColor;
}