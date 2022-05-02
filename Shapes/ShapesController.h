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
		LoadFile,
		ShowCount,
		ShowShapes,
		ShowBiggestAreaShape,
		ShowSmallestPerimeterShape,
		Draw,
		DrawFile,
		Clear,
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
	HandlingResult LoadFile(std::istream& args);
	HandlingResult ShowShapesCount(std::istream& args) const;
	HandlingResult ShowShapes(std::istream& args) const;
	HandlingResult ShowBiggestArea(std::istream& args) const;
	HandlingResult ShowSmallestPerimeter(std::istream& args) const;
	HandlingResult Draw(std::istream& args) const;
	HandlingResult DrawFromFile(std::istream& args);
	HandlingResult Clear(std::istream& args);
	Handler GetActionHandler(Action action);
	void ReadShapesFile(std::ifstream& file);
	void CreateShape(const std::string& shape, std::istringstream& args);

	std::ostream& m_output;
	std::istream& m_input;
	std::vector<std::unique_ptr<IShape>> m_shapes{};

	const ActionMap m_actionMap = {
		{ "line", Action::CreateLineSegment },
		{ "triangle", Action::CreateTriangle },
		{ "rectangle", Action::CreateRectangle },
		{ "circle", Action::CreateCircle },
		{ "loadfile", Action::LoadFile },
		{ "count", Action::ShowCount },
		{ "show", Action::ShowShapes },
		{ "bigarea", Action::ShowBiggestAreaShape },
		{ "smallperim", Action::ShowSmallestPerimeterShape },
		{ "draw",  Action::Draw },
		{ "drawfile", Action::DrawFile },
		{ "clear", Action::Clear },
		{ "help", Action::ShowHelp },
		{ "exit", Action::Exit }
	};
};