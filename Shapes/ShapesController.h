#pragma once
#include "Circle.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Triangle.h"
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>

enum class HandlingResult
{
	Fail,
	Success,
	UnknownCommand,
	Exit
};

class ShapesController
{
public:
	ShapesController(std::istream& input, std::ostream& output);

	HandlingResult HandleCommand();
	void ShowHelp();

private:
	enum class Action
	{
		CreateLineSegment,
		CreateTriangle,
		CreateRectangle,
		CreateCircle,
		ShowShapes,
		ShowBiggestAreaShape,
		ShowSmallestPerimeterShape,
		ShowHelp,
		Exit
	};

	using Handler = std::function<HandlingResult(std::istream& args)>;
	using ActionMap = std::map<std::string, Action>;

	HandlingResult ExecuteHandlingExceptions(Handler handler, std::istream& args);
	HandlingResult CreateLineSegment(std::istream& args);
	HandlingResult CreateTriangle(std::istream& args);
	HandlingResult CreateRectangle(std::istream& args);
	HandlingResult CreateCircle(std::istream& args);
	HandlingResult ShowBiggestArea(std::istream& args);
	HandlingResult ShowSmallestPerimeter(std::istream& args);
	HandlingResult ShowShapes(std::istream& args);
	Handler GetActionHandler(Action action);

	std::ostream& m_output;
	std::istream& m_input;
	std::vector<std::unique_ptr<IShape>> shapes{};

	const ActionMap m_actionMap = {
		{ "line", Action::CreateLineSegment },
		{ "triangle", Action::CreateTriangle },
		{ "rectangle", Action::CreateRectangle },
		{ "circle", Action::CreateCircle },
		{ "show", Action::ShowShapes },
		{ "bigarea", Action::ShowBiggestAreaShape },
		{ "smallperim", Action::ShowSmallestPerimeterShape },
		{ "help", Action::ShowHelp },
		{ "exit", Action::Exit }
	};
};