#include "ShapesController.h"
#include "ShapeParamsCompare.h"
#include <algorithm>
#include <optional>
#include <sstream>

static void ToLowerString(std::string& str);
static std::optional<uint32_t> StringToColorCode(const std::string& str);

ShapesController::ShapesController(std::ostream& output)
	: m_output(output)
{
}

HandlingResult ShapesController::HandleCommand(const std::string& commandLine)
{
	std::istringstream ss(commandLine);
	std::string action{};
	ss >> action;
	ToLowerString(action);

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.cend())
	{
		return ExecuteHandlingExceptions(GetActionHandler(it->second), ss);
	}

	return HandlingResult::UnknownCommand;
}

ShapesController::Handler ShapesController::GetActionHandler(Action action)
{
	switch (action)
	{
	case ShapesController::Action::CreateLineSegment:
		return [this](std::istringstream& args) { return CreateLineSegment(args); };
	case ShapesController::Action::CreateTriangle:
		return [this](std::istringstream& args) { return CreateTriangle(args); };
	case ShapesController::Action::CreateRectangle:
		return [this](std::istringstream& args) { return CreateRectangle(args); };
	case ShapesController::Action::CreateCircle:
		return [this](std::istringstream & args) { return CreateCircle(args); };
	case ShapesController::Action::ShowShapes:
		return [this](std::istringstream& args) { return ShowShapes(args); };
	case ShapesController::Action::ShowBiggestAreaShape:
		return [this](std::istringstream& args) { return ShowBiggestArea(args); };
	case ShapesController::Action::ShowSmallestPerimeterShape:
		return [this](std::istringstream& args) { return ShowSmallestPerimeter(args); };
	case ShapesController::Action::ShowHelp:
		return [this](std::istringstream& args) { ShowHelp(); return HandlingResult::Success; };
	case ShapesController::Action::Exit:
		return [this](std::istringstream& args) { return HandlingResult::Exit; };
	default:
		throw std::runtime_error("No handler for action");
	}
}

HandlingResult ShapesController::ExecuteHandlingExceptions(Handler handler, std::istringstream& args)
{
	try
	{
		return handler(args);
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << std::endl;
		return HandlingResult::Fail;
	}
}

HandlingResult ShapesController::CreateLineSegment(std::istringstream& args)
{
	double x1{}, y1{};
	double x2{}, y2{};
	std::string colorStr{};
	std::optional<uint32_t> color{};

	args >> x1 >> y1 >> x2 >> y2 >> colorStr;

	color = StringToColorCode(colorStr);
	if (!color.has_value())
	{
		throw std::invalid_argument("LineSegment must have color");
	}

	shapes.emplace_back(new LineSegment({ x1, y1 }, { x2, y2 }, color.value()));

	return HandlingResult::Success;
}

HandlingResult ShapesController::CreateTriangle(std::istringstream& args)
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

HandlingResult ShapesController::CreateRectangle(std::istringstream& args)
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

	shapes.emplace_back(new Rectangle({ x1, y1 }, { x2, y2 }, fillColor, outlineColor));

	return HandlingResult::Success;
}

HandlingResult ShapesController::CreateCircle(std::istringstream& args)
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

HandlingResult ShapesController::ShowBiggestArea(std::istringstream&)
{
	if (shapes.empty())
	{
		m_output << "No shapes" << std::endl;
		return HandlingResult::Success;
	}

	auto it = std::max_element(shapes.cbegin(), shapes.cend(), AreaCompare);
	m_output << it->get()->ToString();

	return HandlingResult::Success;
}

HandlingResult ShapesController::ShowSmallestPerimeter(std::istringstream&)
{
	if (shapes.empty())
	{
		m_output << "No shapes" << std::endl;
		return HandlingResult::Success;
	}

	auto it = std::min_element(shapes.cbegin(), shapes.cend(), PerimeterCompare);
	m_output << it->get()->ToString();

	return HandlingResult::Success;
}

HandlingResult ShapesController::ShowShapes(std::istringstream&)
{
	if (shapes.empty())
	{
		m_output << "No shapes" << std::endl;
		return HandlingResult::Success;
	}

	for (const auto& shape : shapes)
	{
		m_output << shape->ToString() << '\n';
	}

	return HandlingResult::Success;
}

void ShapesController::ShowHelp()
{
	m_output << "Add line: line <x1> <y1> <x2> <y2> <color>"
			 << "\nAdd triangle: triangle <x1> <y1> <x2> <y2> <x3> <y3> <fill_color|No> <outline_color|No>"
			 << "\nAdd rectangle: rectangle <x1> <y1> <x2> <y2> <fill_color|No> <outline_color|No>"
			 << "\nAdd circle: circle <x> <y> <radius> <fill_color|No> <outline_color|No>"
			 << "\nShow shapes: show"
			 << "\nShow shape with biggest area: bigarea"
			 << "\nShow shape with smaller perimeter: smallperim"
			 << "\nShow help: help"
			 << "\nExit program: exit"
			 << std::endl;
}

void ToLowerString(std::string& str)
{
	std::transform(str.cbegin(), str.cend(), str.begin(), [](char c) { return tolower(c); });
}

std::optional<uint32_t> StringToColorCode(const std::string& str)
{
	std::string _str{ str };
	ToLowerString(_str);

	if (_str == "no")
	{
		return std::nullopt;
	}

	try
	{
		return std::stoul(_str, 0, 16);
	}
	catch (const std::exception& e)
	{
		throw std::invalid_argument("Wrong color");
	}
}