#pragma once
#include "IShape.h"

class Shape : public virtual IShape
{
public:
	Shape(ShapeType type, std::optional<uint32_t> outlineColor);

	std::string ToString() const override;
	std::optional<uint32_t> GetOutlineColor() const override;

protected:
	static void PrepareStream(std::ostream& os);
	static void ResetStream(std::ostream& os);

	const ShapeType m_shape{};
	std::optional<uint32_t> m_outlineColor{};
};