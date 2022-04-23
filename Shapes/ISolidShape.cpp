#include "ISolidShape.h"

ISolidShape::ISolidShape(ShapeType type, uint32_t fillColor, std::optional<uint32_t> outlineColor)
	: IShape(type, outlineColor)
	, m_fillColor(fillColor)
{
}

ISolidShape::~ISolidShape()
{
}

uint32_t ISolidShape::GetFillColor() const
{
	return m_fillColor;
}