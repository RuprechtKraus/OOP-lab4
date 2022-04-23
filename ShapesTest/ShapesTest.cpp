#include "pch.h"
#include "CppUnitTest.h"
#include "../Shapes/LineSegment.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

double RoundToNDecimalPlaces(double value, int decimalPlaces)
{
	const double multiplier = std::pow(10.0, decimalPlaces);
	return std::floor(value * multiplier) / multiplier;
}

namespace ShapesTest
{
	TEST_CLASS(LineSegmentTest)
	{
	public:
		
		TEST_METHOD(HasLength)
		{
			LineSegment line({ 0.0, 0.0 }, { 5.0, 5.0 });
			Assert::AreEqual(7.07, RoundToNDecimalPlaces(line.GetLength(), 2), 
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

		TEST_METHOD(HasRedOutline)
		{
			LineSegment line({ 0.0, 0.0 }, { 5.0, 5.0 }, 0xff0000u);
			Assert::IsTrue(line.GetOutlineColor().has_value(), L"No outline");
			Assert::AreEqual(0xff0000u, line.GetOutlineColor().value(), L"Outline color is not red");
		}

		TEST_METHOD(HasNoOutline)
		{
			LineSegment line({ 0.0, 0.0 }, { 5.0, 5.0 }, 0xff0000u);
			Assert::IsTrue(line.GetOutlineColor().has_value(), L"No outline");
			Assert::AreEqual(0xff0000u, line.GetOutlineColor().value(), L"Outline color is not red");
		}

		TEST_METHOD(HasLineSegmentType)
		{
			LineSegment line({ 0.0, 0.0 }, { 5.0, 5.0 });
			Assert::AreEqual(std::string{ "LineSegment" }, line.ToString(), L"Incorrect shape type");
		}
	};


}