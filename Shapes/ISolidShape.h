#pragma once
#include "IShape.h"
#include "ShapeType.h"

class ISolidShape : public virtual IShape
{
public:
	virtual std::optional<uint32_t> GetFillColor() const = 0;
};