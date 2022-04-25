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
	using Handler = std::function<HandlingResult(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	HandlingResult ExecuteHandlingExceptions(Handler handler, std::istream& args);
	HandlingResult CreateLineSegment(std::istream& args);
	HandlingResult CreateTriangle(std::istream& args);
	HandlingResult CreateRectangle(std::istream& args);
	HandlingResult CreateCircle(std::istream& args);
	HandlingResult ShowBiggestArea(std::istream& args);
	HandlingResult ShowSmallestPerimeter(std::istream& args);
	HandlingResult ShowShapes(std::istream& args);

	std::ostream& m_output;
	std::istream& m_input;
	std::vector<std::unique_ptr<IShape>> shapes{};
	const ActionMap m_actionMap = {
		{ "line", [this](std::istream& args) { return CreateLineSegment(args); } },
		{ "triangle", [this](std::istream& args) { return CreateTriangle(args); } },
		{ "rectangle", [this](std::istream& args) { return CreateRectangle(args); } }, 
		{ "circle", [this](std::istream& args) { return CreateCircle(args); } },
		{ "show", [this](std::istream& args) { return ShowShapes(args); } },
		{ "bigarea", [this](std::istream& args) { return ShowBiggestArea(args); } },
		{ "smallperim", [this](std::istream& args) { return ShowSmallestPerimeter(args); } },
		{ "help", [this](std::istream& args) { ShowHelp(); return HandlingResult::Success; } },
		{ "exit", [this](std::istream& args) { return HandlingResult::Exit; } }
	};
};