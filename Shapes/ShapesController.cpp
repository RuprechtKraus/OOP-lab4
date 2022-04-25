#include "ShapesController.h"
#include <algorithm>
#include <optional>
#include <sstream>

void ToLowerString(std::string& str);
std::optional<uint32_t> StringToColorCode(const std::string& str);

ShapesController::ShapesController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

HandlingResult ShapesController::HandleCommand()
{
	std::string action{};
	m_input >> action;
	ToLowerString(action);

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.cend())
	{
		return it->second(m_input);
	}

	return HandlingResult::UnknownCommand;
}

HandlingResult ShapesController::CreateLineSegment(std::istream& args)
{
	double x1{}, y1{};
	double x2{}, y2{};
	std::string color{};

	args >> x1 >> y1 >> x2 >> y2 >> color;
	shapes.emplace_back(new LineSegment({ x1, y1 }, { x2, y2 }, std::stoul(color, 0, 16)));

	return HandlingResult::Success;
}

HandlingResult ShapesController::CreateTriangle(std::istream& args)
{
	double x1{}, y1{};
	double x2{}, y2{};
	double x3{}, y3{};
	std::string fillColorStr{};
	std::string outlineColorStr{};
	std::optional<uint32_t> fillColor{};
	std::optional<uint32_t> outlineColor{};

	args >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> fillColorStr >> outlineColorStr;

	fillColor = StringToColorCode(fillColorStr);
	outlineColor = StringToColorCode(outlineColorStr);

	shapes.emplace_back(new Triangle({ x1, y1 }, { x2, y2 }, { x3, y3 }, fillColor, outlineColor));

	return HandlingResult::Success;
}

HandlingResult ShapesController::CreateRectangle(std::istream& args)
{
	double x1{}, y1{};
	double x2{}, y2{};
	std::string fillColorStr{};
	std::string outlineColorStr{};
	std::optional<uint32_t> fillColor{};
	std::optional<uint32_t> outlineColor{};

	args >> x1 >> y1 >> x2 >> y2 >> fillColorStr >> outlineColorStr;

	fillColor = StringToColorCode(fillColorStr);
	outlineColor = StringToColorCode(outlineColorStr);

	shapes.emplace_back(new Rectangle({ x1, y1 }, {x2,y2}, fillColor, outlineColor));

	return HandlingResult::Success;
}

HandlingResult ShapesController::CreateCircle(std::istream& args)
{
	double x{}, y{};
	double radius{};
	std::string fillColorStr{};
	std::string outlineColorStr{};
	std::optional<uint32_t> fillColor{};
	std::optional<uint32_t> outlineColor{};

	args >> x >> y >> radius >> fillColorStr >> outlineColorStr;

	fillColor = StringToColorCode(fillColorStr);
	outlineColor = StringToColorCode(outlineColorStr);

	shapes.emplace_back(new Circle({ x, y }, radius, fillColor, outlineColor));

	return HandlingResult::Success;
}

void ShapesController::ShowHelp()
{
	m_output << "Add line: line <x1> <y1> <x2> <y2> <color>"
			 << "\nAdd triangle: triangle <x1> <y1> <x2> <y2> <x3> <y3> <fill_color|No> <outline_color|No>"
			 << "\nAdd rectangle: rectangle <x1> <y1> <x2> <y2> <fill_color|No> <outline_color|No>"
			 << "\nAdd circle: circle <x> <y> <radius> <fill_color|No> <outline_color|No>"
			 << "\nShow shapes: show"
			 << "\nShow help: help"
			 << "\nExit program: exit"
			 << std::endl;
}

void ShapesController::ShowShapes()
{
	for (const auto& shape : shapes)
	{
		m_output << shape->ToString() << '\n';
	}
}

void ToLowerString(std::string& str)
{
	std::transform(str.cbegin(), str.cend(), str.begin(), [](char c) { return tolower(c); });
}

std::optional<uint32_t> StringToColorCode(const std::string& str)
{
	std::string _str{ str };
	ToLowerString(_str);

	if (_str != "no")
	{
		return std::stoul(_str, 0, 16);
	}

	return std::nullopt;
}