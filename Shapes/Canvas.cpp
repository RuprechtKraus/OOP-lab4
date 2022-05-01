#include "Canvas.h"

Canvas::Canvas(sf::RenderWindow& window)
	: m_window(window)
{
}

sf::Color HexToRGBA(uint32_t hexColor);

void SetShapeColors(sf::Shape& shape, 
	std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor);

void SetShapeFillColor(sf::Shape& shape, std::optional<uint32_t> fillColor);

void SetShapeOutlineColor(sf::Shape& shape, std::optional<uint32_t> outlineColor);

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
	SetShapeColors(convex, fillColor, outlineColor);

	m_window.draw(convex);
}

void Canvas::DrawCircle(const Point& center, double radius,
	std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor)
{
	sf::CircleShape circle(static_cast<float>(radius));

	circle.move(static_cast<float>(center.x), static_cast<float>(center.y));
	circle.setOutlineThickness(1);
	SetShapeColors(circle, fillColor, outlineColor);

	m_window.draw(circle);
}

sf::Color HexToRGBA(uint32_t hexColor)
{
	return sf::Color((hexColor << 8) | 0x000000FFU);
}

void SetShapeColors(sf::Shape& shape, 
	std::optional<uint32_t> fillColor, std::optional<uint32_t> outlineColor)
{
	SetShapeFillColor(shape, fillColor);
	SetShapeOutlineColor(shape, outlineColor);
}

void SetShapeFillColor(sf::Shape& shape, std::optional<uint32_t> fillColor)
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

void SetShapeOutlineColor(sf::Shape& shape, std::optional<uint32_t> outlineColor)
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