#pragma once
#include "IShape.h"
#include "ShapeType.h"

class ISolidShape : public IShape //TODO: Убрать реализацию из интерфейсов в абстрактный класс
{
public:
	ISolidShape(ShapeType type, std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor);
	virtual ~ISolidShape() = default;

	std::optional<uint32_t> GetFillColor() const;
	std::string ToString() const override;

protected:
	std::optional<uint32_t> m_fillColor{};
};