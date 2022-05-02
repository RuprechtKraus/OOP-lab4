#pragma once
#include "ICanvasDrawable.h"
#include "ShapeType.h"
#include <optional>
#include <string>

class IShape : public ICanvasDrawable
{
public:
	virtual ~IShape() = default;

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual std::optional<uint32_t> GetOutlineColor() const = 0;
};