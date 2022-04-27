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
	ShapesController(std::ostream& output);

	HandlingResult HandleCommand(const std::string& commandLine);
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

	using Handler = std::function<HandlingResult(std::istringstream& args)>;
	using ActionMap = std::map<std::string, Action>;

	HandlingResult ExecuteHandlingExceptions(Handler handler, std::istringstream& args);
	HandlingResult CreateLineSegment(std::istringstream& args);
	HandlingResult CreateTriangle(std::istringstream& args);
	HandlingResult CreateRectangle(std::istringstream& args);
	HandlingResult CreateCircle(std::istringstream& args);
	HandlingResult ShowBiggestArea(std::istringstream& args);
	HandlingResult ShowSmallestPerimeter(std::istringstream& args);
	HandlingResult ShowShapes(std::istringstream& args);
	Handler GetActionHandler(Action action);

	std::ostream& m_output;
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