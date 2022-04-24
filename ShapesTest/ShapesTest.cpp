﻿#include "pch.h"
#include "Circle.h"
#include "CppUnitTest.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Triangle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

double RoundNumber(double value, int decimalPlaces)
{
	const double multiplier = std::pow(10.0, decimalPlaces);
	return std::round(value * multiplier) / multiplier;
}

namespace ShapesTest
{
	TEST_CLASS(LineSegmentTest)
	{
		TEST_METHOD(HasLength)
		{
			LineSegment line({ 0.0, 0.0 }, { 5.0, 5.0 });
			Assert::AreEqual(7.1, RoundNumber(line.GetLength(), 1), 
				L"Length is incorrect");
		}

		TEST_METHOD(HasZeroPerimeter)
		{
			LineSegment line({ 0.0, 0.0 }, { 5.0, 5.0 });
			Assert::AreEqual(0.0, line.GetPerimeter(), L"Line has a perimeter");
		}

		TEST_METHOD(HasStartAndEndPoints)
		{
			LineSegment line({ 0.0, 0.0 }, { 5.0, 5.0 });
			Point start{ line.GetStartPoint() };
			Point end{ line.GetEndPoint() };
			Assert::IsTrue(start.x == 0.0 && start.y == 0.0, L"Start point is incorrect");
			Assert::IsTrue(end.x == 5.0 && end.y == 5.0, L"Start point is incorrect");
		}

		TEST_METHOD(HasBlackColorByDefault)
		{
			LineSegment line({ 0.0, 0.0 }, { 5.0, 5.0 });
			Assert::AreEqual(0x000000U, line.GetColor(), L"Color isn't black");
		}

		TEST_METHOD(HasYellowColor)
		{
			LineSegment line({ 0.0, 0.0 }, { 5.0, 5.0 }, 0xFFFF00U);
			Assert::AreEqual(0xFFFF00U, line.GetColor(), L"Color isn't yellow");
		}

		TEST_METHOD(CanBeConvertedToString)
		{
			LineSegment line({ 0.0, 0.0 }, { 5.5, 5.5 }, 0xFF0000U);
			std::string expectedString{ R"(Type: LineSegment
Color: 0XFF0000
Start: 0.0, 0.0
End: 5.5, 5.5
Length: 7.8
)" };
			Assert::AreEqual(expectedString, line.ToString(), L"Convertation to string failed");
		}
	};

	TEST_CLASS(TriangleTest)
	{
		TEST_METHOD(HasVertices)
		{
			Triangle triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 });
			Point v1 = triangle.GetVertex1();
			Point v2 = triangle.GetVertex2();
			Point v3 = triangle.GetVertex3();

			Assert::IsTrue(v1.x == 0.0 && v1.y == 0.0, L"First vertex is incorrect");
			Assert::IsTrue(v2.x == 2.0 && v2.y == 4.0, L"First second is incorrect");
			Assert::IsTrue(v3.x == 4.0 && v3.y == 0.0, L"First third is incorrect");
		}

		TEST_METHOD(HasArea)
		{
			Triangle triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 });
			Assert::AreEqual(8.0, triangle.GetArea(), L"Are is incorrect");
		}

		TEST_METHOD(HasPerimeter)
		{
			Triangle triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 });
			Assert::AreEqual(12.94, RoundNumber(triangle.GetPerimeter(), 2), L"Perimeter is incorrect");
		}

		TEST_METHOD(HasWhiteFillColorByDefault)
		{
			Triangle triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 });
			Assert::AreEqual(0xFFFFFFU, triangle.GetFillColor(), L"Fill color is not black");
		}

		TEST_METHOD(HasGreenFillColor)
		{
			Triangle triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 }, 0x00FF00U);
			Assert::AreEqual(0x00FF00U, triangle.GetFillColor(), L"Fill color is not green");
		}

		TEST_METHOD(HasNoOutline)
		{
			Triangle triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 }, 0x00FF00U);
			Assert::IsFalse(triangle.GetOutlineColor().has_value(), L"Has outline");
		}

		TEST_METHOD(HasBlueOutlineColor)
		{
			Triangle triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 }, 0x00FF00U, 0x0000FFU);
			Assert::IsTrue(triangle.GetOutlineColor().has_value(), L"No outline");
			Assert::AreEqual(0x0000FFU, triangle.GetOutlineColor().value(), L"Outline color is not blue");
		}

		TEST_METHOD(CanBeConvertedToString)
		{
			Triangle triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 }, 0x00FF00U, 0x0000FFU);
			std::string expectedString{ R"(Type: Triangle
Area: 8.0
Perimeter: 12.9
Fill color: 0XFF00
Outline color: 0XFF
Vertex 1: 0.0, 0.0
Vertex 2: 2.0, 4.0
Vertex 3: 4.0, 0.0
Edge A length: 4.5
Edge B length: 4.0
Edge C length: 4.5
)" };
			Assert::AreEqual(expectedString, triangle.ToString(), L"Convertation to string failed");
		}
	};

	TEST_CLASS(RectangleTest)
	{
		TEST_METHOD(CantCreateWithBottomRightBeingToTheLeftOfTopLeft)
		{
			auto rectangleCreate = []() { Rectangle rectangle({ 10.0, 10.0 }, { 5.0, 5.0 }); };
			Assert::ExpectException<std::invalid_argument>(rectangleCreate, L"Bottom right is to the left of top left");
		}

		TEST_METHOD(CantCreateWithBottomRightBeingAboveOfTopLeft)
		{
			auto rectangleCreate = []() { Rectangle rectangle({ 10.0, 10.0 }, { 15.0, 20.0 }); };
			Assert::ExpectException<std::invalid_argument>(rectangleCreate, L"Bottom right is above of top left");
		}

		TEST_METHOD(HasArea)
		{
			Rectangle rectangle({ 10.0, 10.0 }, { 20.0, 5.0 });
			Assert::AreEqual(50.0, rectangle.GetArea(), L"Area is incorrect");
		}

		TEST_METHOD(HasPerimeter)
		{
			Rectangle rectangle({ 10.0, 10.0 }, { 20.0, 5.0 });
			Assert::AreEqual(30.0, rectangle.GetPerimeter(), L"Perimeter is incorrect");
		}

		TEST_METHOD(HasWidth)
		{
			Rectangle rectangle({ 10.0, 10.0 }, { 20.0, 5.0 });
			Assert::AreEqual(10.0, rectangle.GetWidth(), L"Width is incorrect");
		}

		TEST_METHOD(HasHeight)
		{
			Rectangle rectangle({ 10.0, 10.0 }, { 20.0, 5.0 });
			Assert::AreEqual(5.0, rectangle.GetHeight(), L"Height is incorrect");
		}

		TEST_METHOD(HasTopLeft)
		{
			Rectangle rectangle({ 10.0, 10.0 }, { 20.0, 5.0 });
			Point topLeft = rectangle.GetTopLeft();
			Assert::IsTrue(topLeft.x == 10.0 && topLeft.y == 10.0, L"Top left corner is incorrect");
		}

		TEST_METHOD(HasBottomRight)
		{
			Rectangle rectangle({ 10.0, 10.0 }, { 20.0, 5.0 });
			Point bottomRight = rectangle.GetBottomRight();
			Assert::IsTrue(bottomRight.x == 20.0 && bottomRight.y == 5.0, L"Top left corner is incorrect");
		}

		TEST_METHOD(HasWhiteFillColorByDefault)
		{
			Rectangle rectangle({ 10.0, 10.0 }, { 20.0, 5.0 });
			Assert::AreEqual(0xFFFFFFU, rectangle.GetFillColor(), L"Fill color is not black");
		}

		TEST_METHOD(HasGreenFillColor)
		{
			Rectangle rectangle({ 10.0, 10.0 }, { 20.0, 5.0 }, 0x00FF00U);
			Assert::AreEqual(0x00FF00U, rectangle.GetFillColor(), L"Fill color is not green");
		}

		TEST_METHOD(HasNoOutline)
		{
			Rectangle rectangle({ 10.0, 10.0 }, { 20.0, 5.0 }, 0x00FF00U);
			Assert::IsFalse(rectangle.GetOutlineColor().has_value(), L"Has outline");
		}

		TEST_METHOD(HasBlueOutlineColor)
		{
			Rectangle rectangle({ 10.0, 10.0 }, { 20.0, 5.0 }, 0x00FF00U, 0x0000FFU);
			Assert::IsTrue(rectangle.GetOutlineColor().has_value(), L"No outline");
			Assert::AreEqual(0x0000FFU, rectangle.GetOutlineColor().value(), L"Outline color is not blue");
		}

		TEST_METHOD(CanBeConvertedToString)
		{
			Rectangle rectangle({ 10.0, 10.0 }, { 20.0, 5.0 }, 0x00FF00U, 0x0000FFU);
			std::string expectedString{ R"(Type: Rectangle
Area: 50.0
Perimeter: 30.0
Fill color: 0XFF00
Outline color: 0XFF
Top left: 10.0, 10.0
Bottom right: 20.0, 5.0
Width: 10.0
Height: 5.0
)" };
			Assert::AreEqual(expectedString, rectangle.ToString(), L"Convertation to string failed");
		}
	};

	TEST_CLASS(CircleTest)
	{
		TEST_METHOD(CantCreateWithNegativeRadius)
		{
			auto circleCreate = []() { Circle circle({ 20.0, 25.0 }, -10.0); };
			Assert::ExpectException<std::invalid_argument>(circleCreate, L"Negative radius");
		}

		TEST_METHOD(HasArea)
		{
			Circle circle({ 20.0, 25.0 }, 10.0);
			Assert::AreEqual(314.16, RoundNumber(circle.GetArea(), 2), L"Area is incorrect");
		}

		TEST_METHOD(HasPerimeter)
		{
			Circle circle({ 20.0, 25.0 }, 10.0);
			Assert::AreEqual(62.83, RoundNumber(circle.GetPerimeter(), 2), L"Perimeter is incorrect");
		}

		TEST_METHOD(HasCenter)
		{
			Circle circle({ 20.0, 25.0 }, 10.0);
			Point center = circle.GetCenter();
			Assert::IsTrue(center.x == 20.0 && center.y == 25.0, L"Center is incorrect");
		}

		TEST_METHOD(HasRadius)
		{
			Circle circle({ 20.0, 25.0 }, 10.0);
			Assert::AreEqual(10.0, circle.GetRadius(), L"Radius is incorrect");
		}

		TEST_METHOD(HasWhiteFillColorByDefault)
		{
			Circle circle({ 20.0, 25.0 }, 10.0);
			Assert::AreEqual(0xFFFFFFU, circle.GetFillColor(), L"Fill color is not black");
		}

		TEST_METHOD(HasGreenFillColor)
		{
			Circle circle({ 20.0, 25.0 }, 10.0, 0x00FF00U);
			Assert::AreEqual(0x00FF00U, circle.GetFillColor(), L"Fill color is not green");
		}

		TEST_METHOD(HasNoOutline)
		{
			Circle circle({ 20.0, 25.0 }, 10.0, 0x00FF00U);
			Assert::IsFalse(circle.GetOutlineColor().has_value(), L"Has outline");
		}

		TEST_METHOD(HasBlueOutlineColor)
		{
			Circle circle({ 20.0, 25.0 }, 10.0, 0x00FF00U, 0x0000FFU);
			Assert::IsTrue(circle.GetOutlineColor().has_value(), L"No outline");
			Assert::AreEqual(0x0000FFU, circle.GetOutlineColor().value(), L"Outline color is not blue");
		}

		TEST_METHOD(CanBeConvertedToString)
		{
			Circle circle({ 20.0, 25.0 }, 10.0, 0x00FF00U, 0x0000FFU);
			std::string expectedString{ R"(Type: Circle
Area: 314.2
Perimeter: 62.8
Fill color: 0XFF00
Outline color: 0XFF
Center: 20.0, 25.0
Radius: 10.0
)" };
			Assert::AreEqual(expectedString, circle.ToString(), L"Convertation to string failed");
		}
	};
}