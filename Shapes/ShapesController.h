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
	using Handler = std::function<HandlingResult(std::istringstream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	HandlingResult ExecuteHandlingExceptions(Handler handler, std::istringstream& args);
	HandlingResult CreateLineSegment(std::istringstream& args);
	HandlingResult CreateTriangle(std::istringstream& args);
	HandlingResult CreateRectangle(std::istringstream& args);
	HandlingResult CreateCircle(std::istringstream& args);
	HandlingResult ShowBiggestArea(std::istringstream& args);
	HandlingResult ShowSmallestPerimeter(std::istringstream& args);
	HandlingResult ShowShapes(std::istringstream& args);

	std::ostream& m_output;
	std::vector<std::unique_ptr<IShape>> shapes{};
	const ActionMap m_actionMap = {
		{ "line", [this](std::istringstream& args) { return CreateLineSegment(args); } },
		{ "triangle", [this](std::istringstream& args) { return CreateTriangle(args); } },
		{ "rectangle", [this](std::istringstream& args) { return CreateRectangle(args); } }, 
		{ "circle", [this](std::istringstream& args) { return CreateCircle(args); } },
		{ "show", [this](std::istringstream& args) { return ShowShapes(args); } },
		{ "bigarea", [this](std::istringstream& args) { return ShowBiggestArea(args); } },
		{ "smallperim", [this](std::istringstream& args) { return ShowSmallestPerimeter(args); } },
		{ "help", [this](std::istringstream& args) { ShowHelp(); return HandlingResult::Success; } },
		{ "exit", [this](std::istringstream& args) { return HandlingResult::Exit; } }
	};
};