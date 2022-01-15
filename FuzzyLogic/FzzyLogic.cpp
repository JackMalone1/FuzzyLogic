#include "FzzyLogic.h"


namespace Fzzy
{
	namespace LogicalOperators
	{
		double FuzzyAnd(double A, double B)
		{
			return std::min(A, B);
		}
		double FuzzyOr(double A, double B)
		{
			return std::max(A, B);
		}
		double FuzzyNot(double A, double B)
		{
			return 1.0 - A;
		}
	}
}