#pragma once
#include "ICanvas.h"
#include <optional>
#include <SFML/Graphics.hpp>

class Canvas final : public ICanvas
{
public:
	Canvas(sf::RenderWindow& window);

	void DrawLine(const Point& start, const Point& end, uint32_t color) override;
	void DrawPolygon(const std::vector<Point>& points,
		std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor) override;
	void DrawCircle(const Point& center, double radius,
		std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor) override;

private:
	sf::RenderWindow& m_window;
};