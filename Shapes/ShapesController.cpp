#include "ShapesController.h"
#include "Canvas.h"
#include "ShapeParamsCompare.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <fstream>
#include <optional>
#include <sstream>

static void ToLowerString(std::string& str);
static std::optional<uint32_t> StringToColorCode(const std::string& str);
static bool IsStringEmpty(const std::string& str);

ShapesController::ShapesController(std::istream& input, std::ostream& output)
	: m_input(&input)
	, m_output(&output)
{
}

HandlingResult ShapesController::HandleCommand()
{
	std::string action{};
	*m_input >> action;
	ToLowerString(action);

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.cend())
	{
		return ExecuteHandlingExceptions(GetActionHandler(it->second), *m_input);
	}

	return HandlingResult::UnknownCommand;
}

ShapesController::Handler ShapesController::GetActionHandler(Action action)
{
	switch (action)
	{
	case Action::CreateLineSegment:
		return [this](std::istream& args) { return CreateLineSegment(args); };
	case Action::CreateTriangle:
		return [this](std::istream& args) { return CreateTriangle(args); };
	case Action::CreateRectangle:
		return [this](std::istream& args) { return CreateRectangle(args); };
	case Action::CreateCircle:
		return [this](std::istream& args) { return CreateCircle(args); };
	case Action::LoadFile:
		return [this](std::istream& args) { return LoadFile(args); };
	case Action::ShowCount:
		return [this](std::istream& args) { return ShowShapesCount(args); };
	case Action::ShowShapes:
		return [this](std::istream& args) { return ShowShapes(args); };
	case Action::ShowBiggestAreaShape:
		return [this](std::istream& args) { return ShowBiggestArea(args); };
	case Action::ShowSmallestPerimeterShape:
		return [this](std::istream& args) { return ShowSmallestPerimeter(args); };
	case Action::Draw:
		return [this](std::istream& args) { return Draw(args); };
	case Action::Clear:
		return [this](std::istream& args) { return Clear(args); };
	case Action::ShowHelp:
		return [this](std::istream& args) { ShowHelp(); return HandlingResult::Success; };
	case Action::Exit:
		return [this](std::istream& args) { return HandlingResult::Exit; };
	default:
		throw std::runtime_error("No handler for action");
	}
}

HandlingResult ShapesController::ExecuteHandlingExceptions(Handler handler, std::istream& args)
{
	try
	{
		return handler(args);
	}
	catch (const std::exception& e)
	{
		*m_output << e.what() << std::endl;
		return HandlingResult::Fail;
	}
}

HandlingResult ShapesController::CreateLineSegment(std::istream& args)
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

	m_shapes.emplace_back(new LineSegment({ x1, y1 }, { x2, y2 }, color.value()));

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

	m_shapes.emplace_back(new Triangle({ x1, y1 }, { x2, y2 }, { x3, y3 }, fillColor, outlineColor));

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

	m_shapes.emplace_back(new Rectangle({ x1, y1 }, { x2, y2 }, fillColor, outlineColor));

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

	m_shapes.emplace_back(new Circle({ x, y }, radius, fillColor, outlineColor));

	return HandlingResult::Success;
}

HandlingResult ShapesController::LoadFile(std::istream& args)
{
	std::string fileName{};
	args >> fileName;
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}

	std::istream* oldStream = m_input;
	ReadShapesFile(file);
	m_input = oldStream;

	*m_output << "File has been loaded" << std::endl;

	return HandlingResult::Success;
}

HandlingResult ShapesController::ShowShapesCount(std::istream&) const
{
	*m_output << m_shapes.size() << std::endl;
	return HandlingResult::Success;
}

HandlingResult ShapesController::ShowShapes(std::istream&) const
{
	if (m_shapes.empty())
	{
		*m_output << "No shapes" << std::endl;
		return HandlingResult::Success;
	}

	for (const auto& shape : m_shapes)
	{
		*m_output << shape->ToString() << '\n';
	}

	return HandlingResult::Success;
}

HandlingResult ShapesController::ShowBiggestArea(std::istream&) const
{
	if (m_shapes.empty())
	{
		*m_output << "No shapes" << std::endl;
		return HandlingResult::Success;
	}

	auto it = std::max_element(m_shapes.cbegin(), m_shapes.cend(), AreaCompare);
	*m_output << it->get()->ToString();

	return HandlingResult::Success;
}

HandlingResult ShapesController::ShowSmallestPerimeter(std::istream&) const
{
	if (m_shapes.empty())
	{
		*m_output << "No shapes" << std::endl;
		return HandlingResult::Success;
	}

	auto it = std::min_element(m_shapes.cbegin(), m_shapes.cend(), PerimeterCompare);
	*m_output << it->get()->ToString();

	return HandlingResult::Success;
}

HandlingResult ShapesController::Draw(std::istream&) const
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Shapes", sf::Style::Close);
	sf::Event event{};
	Canvas canvas(window);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color(255, 255, 255));

		for (const auto& shape : m_shapes)
		{
			shape->Draw(canvas);
		}

		window.display();
	}

	return HandlingResult::Success;
}

HandlingResult ShapesController::Clear(std::istream&)
{
	m_shapes.clear();
	*m_output << "All shapes have been deleted" << std::endl;
	return HandlingResult::Success;
}

void ShapesController::ShowHelp()
{
	*m_output << "Add line: line <x1> <y1> <x2> <y2> <color>"
			  << "\nAdd triangle: triangle <x1> <y1> <x2> <y2> <x3> <y3> <fill_color|No> <outline_color|No>"
			  << "\nAdd rectangle: rectangle <x1> <y1> <x2> <y2> <fill_color|No> <outline_color|No>"
			  << "\nAdd circle: circle <x> <y> <radius> <fill_color|No> <outline_color|No>"
			  << "\nLoad shapes from file: loadfile <file_name>"
			  << "\nShow shapes count: count"
			  << "\nShow shapes: show"
			  << "\nShow shape with biggest area: bigarea"
			  << "\nShow shape with smaller perimeter: smallperim"
			  << "\nDraw shapes: draw"
			  << "\nClear shape list: clear"
			  << "\nShow help: help"
			  << "\nExit program: exit"
			  << std::endl;
}

void ShapesController::ReadShapesFile(std::ifstream& file)
{
	std::string line{};
	while (std::getline(file, line))
	{
		if (!IsStringEmpty(line))
		{
			std::istringstream ss(line);
			m_input = &ss;
			HandleCommand();
		}
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

	if (_str == "no")
	{
		return std::nullopt;
	}

	try
	{
		return std::stoul(_str, 0, 16);
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument("Wrong color");
	}
}

static bool IsStringEmpty(const std::string& str)
{
	return str.empty() || std::all_of(str.cbegin(), str.cend(), [](char c) { return c == ' '; });
}