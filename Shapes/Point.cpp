#include "Point.h"
#include <cmath>

double Distance(Point p1, Point p2)
{
	return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}