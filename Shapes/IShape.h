#pragma once
#include "ShapeType.h"
#include <optional>
#include <string>
#include "ICanvasDrawable.h"

class IShape : public ICanvasDrawable
{
public:
	IShape(ShapeType type, std::optional<uint32_t> outlineColor);
	virtual ~IShape() = default;

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const;
	std::optional<uint32_t> GetOutlineColor() const;

protected:
	static void PrepareStream(std::ostream& os);
	static void ResetStream(std::ostream& os);

	const ShapeType m_shape{};
	std::optional<uint32_t> m_outlineColor{};
};