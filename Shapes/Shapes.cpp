#include <iostream>
#include "LineSegment.h"
#include "Triangle.h"
#include "IShape.h"

int main()
{
	LineSegment line({ 0.0, 0.0 }, { 5.5, 5.5 }, 0xFFFFFF);
	Triangle triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 }, 0x0000FF, 0xFF0000);

	IShape* shape = &line;
	std::cout << shape->ToString() << '\n';

	shape = &triangle;
	std::cout << shape->ToString();
}