#include "IShape.h"

IShape::IShape(ShapeType type, std::optional<uint32_t> outlineColor)
	: m_shape(type)
	, m_outlineColor(outlineColor)
{
}

std::string IShape::ToString() const
{
	return ShapeToString(m_shape);
}

std::optional<uint32_t> IShape::GetOutlineColor() const
{
	return m_outlineColor;
}