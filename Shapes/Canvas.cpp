#include "Canvas.h"

Canvas::Canvas(sf::RenderWindow& window)
	: m_window(window)
{
}

sf::Color HexToRGBA(uint32_t hexColor);

void SetPolygonColors(sf::ConvexShape& shape, 
	std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor);

void SetPolygonFillColor(sf::ConvexShape& shape, std::optional<uint32_t> fillColor);

void SetPolygonOutlineColor(sf::ConvexShape& shape, std::optional<uint32_t> outlineColor);

void Canvas::DrawLine(const Point& start, const Point& end, uint32_t color)
{
	sf::Color rgba{ HexToRGBA(color) };

	sf::Vertex line[2]{
		sf::Vertex(sf::Vector2f(static_cast<float>(start.x), static_cast<float>(start.y)), rgba),
		sf::Vertex(sf::Vector2f(static_cast<float>(end.x), static_cast<float>(end.y)), rgba)
	};

	m_window.draw(line, 2, sf::Lines);
}

void Canvas::DrawPolygon(const std::vector<Point>& points,
	std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor)
{
	sf::ConvexShape convex(points.size());

	for (size_t i = 0; i < points.size(); i++)
	{
		convex.setPoint(i, sf::Vector2f(static_cast<float>(points[i].x), static_cast<float>(points[i].y)));
	}

	convex.setOutlineThickness(1);
	SetPolygonColors(convex, fillColor, outlineColor);

	m_window.draw(convex);
}

void Canvas::DrawCircle(const Point& center, double radius,
	std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor)
{
}

sf::Color HexToRGBA(uint32_t hexColor)
{
	return sf::Color((hexColor << 8) | 0x000000FFU);
}

void SetPolygonColors(sf::ConvexShape& shape, 
	std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor)
{
	SetPolygonFillColor(shape, fillColor);
	SetPolygonOutlineColor(shape, outlineColor);
}

void SetPolygonFillColor(sf::ConvexShape& shape, std::optional<uint32_t> fillColor)
{
	if (fillColor)
	{
		shape.setFillColor(HexToRGBA(fillColor.value()));
	}
	else
	{
		shape.setFillColor(sf::Color(0, 0, 0, 0));
	}
}

void SetPolygonOutlineColor(sf::ConvexShape& shape, std::optional<uint32_t> outlineColor)
{
	if (outlineColor)
	{
		shape.setOutlineColor(HexToRGBA(outlineColor.value()));
	}
	else
	{
		shape.setOutlineColor(sf::Color(0, 0, 0, 0));
	}
}