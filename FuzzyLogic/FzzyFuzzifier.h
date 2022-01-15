#pragma once

namespace Fzzy
{
	namespace Fuzzifier
	{
		double FuzzyGrade(double value, double x0, double x1);
		double FuzzyTriangle(double value, double x0, double x1, double x2);
		double FuzzyTrapezoid(double value, double x0, double x1, double x2, double x3);
	}
}