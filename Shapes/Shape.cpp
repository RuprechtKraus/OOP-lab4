#include "Shape.h"
#include <sstream>

Shape::Shape(ShapeType type, std::optional<uint32_t> outlineColor)
	: m_shape(type)
	, m_outlineColor(outlineColor)
{
}

std::optional<uint32_t> Shape::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string Shape::ToString() const
{
	std::ostringstream ss;
	ss << "Type: " << ShapeToString(m_shape);
	return ss.str();
}

void Shape::PrepareStream(std::ostream& os)
{
	os.precision(1);
	os << std::fixed << std::hex << std::uppercase << std::showbase;
}

void Shape::ResetStream(std::ostream& os)
{
	os.precision(6);
	os << std::defaultfloat << std::dec << std::nouppercase << std::noshowbase;
}