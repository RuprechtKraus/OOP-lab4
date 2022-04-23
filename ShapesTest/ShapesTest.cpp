#include "pch.h"
#include "CppUnitTest.h"
#include "../Shapes/LineSegment.h"
#include "../Shapes/Triangle.h"

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
	public:
		
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
Outline: none
Color: 0XFF0000
Start: 0, 0
End: 5.5, 5.5
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

		TEST_METHOD(HasBlueOutlinelColor)
		{
			Triangle triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 }, 0x00FF00U, 0x0000FFU);
			Assert::IsTrue(triangle.GetOutlineColor().has_value(), L"No outline");
			Assert::AreEqual(0x0000FFU, triangle.GetOutlineColor().value(), L"Outline color is not blue");
		}
	};
}