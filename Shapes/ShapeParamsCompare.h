#pragma once
#include "IShape.h"
#include <memory>

static bool AreaCompare(const std::unique_ptr<IShape>& left, const std::unique_ptr<IShape>& right) //TODO: Перенести в ShapesController.cpp
{
	return left->GetArea() < right->GetArea();
}

static bool PerimeterCompare(const std::unique_ptr<IShape>& left, const std::unique_ptr<IShape>& right)
{
	return left->GetPerimeter() < right->GetPerimeter();
}