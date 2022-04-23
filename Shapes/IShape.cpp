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

std::optional<uint32_t> IShape::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string IShape::ToString() const
{
	std::ostringstream ss;
	ss << "Type: " << ShapeToString(m_shape);
	return ss.str();
}

void IShape::PrepareStream(std::ostream& os)
{
	os.precision(1);
	os << std::fixed << std::hex << std::uppercase << std::showbase;
}

void IShape::ResetStream(std::ostream& os)
{
	os.precision(6);
	os << std::defaultfloat << std::dec << std::nouppercase << std::noshowbase;
}