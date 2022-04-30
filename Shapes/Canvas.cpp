#include "Canvas.h"

Canvas::Canvas(sf::RenderWindow& window)
	: m_window(window)
{
}

sf::Color HexToRGBA(uint32_t hexColor);

void Canvas::DrawLine(const Point& start, const Point& end, uint32_t color)
{
	sf::Color rgba{ HexToRGBA(color) };

	sf::Vertex line[2] = {
		sf::Vertex(sf::Vector2f(static_cast<float>(start.x), static_cast<float>(start.y)), rgba),
		sf::Vertex(sf::Vector2f(static_cast<float>(end.x), static_cast<float>(end.y)), rgba)
	};

	m_window.draw(line, 2, sf::Lines);
}

void Canvas::DrawPolygon(const std::vector<Point>& points,
	std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor)
{
}

void Canvas::DrawCircle(const Point& center, double radius,
	std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor)
{
}

sf::Color HexToRGBA(uint32_t hexColor)
{
	return sf::Color((hexColor << 8) | 0x000000FFU);
}