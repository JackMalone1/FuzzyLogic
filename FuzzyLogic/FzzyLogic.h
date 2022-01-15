#pragma once
#include <algorithm>

namespace Fzzy
{
	namespace LogicalOperators
	{
		double FuzzyAnd(double A, double B);
		double FuzzyOr(double A, double B);
		double FuzzyNot(double A, double B);
	}
}