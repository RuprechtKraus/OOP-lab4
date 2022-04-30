#pragma once
#include "Point.h"
#include <vector>
#include <optional>

class ICanvas
{
	virtual ~ICanvas() = default;

	virtual void DrawLine(const Point& start, const Point& end, uint32_t color) = 0;
	virtual void DrawPolygon(const std::vector<Point>& points, 
		std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor) = 0;
	virtual void DrawCircle(const Point& center, double radius, 
		std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor) = 0;
};