#include "IShape.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Triangle.h"
#include <iostream>

int main()
{
	LineSegment line({ 0.0, 0.0 }, { 5.5, 5.5 }, 0xFFFFFF);
	Triangle triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 }, 0x0000FF, 0xFF0000);
	Rectangle rectangle({ 10.0, 10.0 }, { 20.0, 5.0 }, 0xFFFF00U, 0xFF00FFU);

	IShape* shape = &line;
	std::cout << shape->ToString() << '\n';

	shape = &triangle;
	std::cout << shape->ToString() << '\n';

	shape = &rectangle;
	std::cout << shape->ToString() << '\n';
}