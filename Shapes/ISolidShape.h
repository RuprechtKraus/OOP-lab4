#pragma once
#include "IShape.h"
#include "ShapeType.h"

class ISolidShape : public IShape 
{
public:
	ISolidShape(ShapeType type, uint32_t fillColor, std::optional<uint32_t> outlineColor);
	virtual ~ISolidShape();

	uint32_t GetFillColor() const;

private:
	uint32_t m_fillColor{};
};