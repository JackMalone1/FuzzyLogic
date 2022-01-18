#include "FzzyFuzzifier.h"

void Fzzy::Fuzzifier::SetUpRuleMatrix(ruleMatrix& matrix)
{
	matrix.m_tiny = Fzzy::Fuzzifier::FuzzyTriangle(8, -10, 0, 10);
	matrix.m_small = Fzzy::Fuzzifier::FuzzyTrapezoid(8, 2.5, 10, 15, 20);
	matrix.m_moderate = Fzzy::Fuzzifier::FuzzyTrapezoid(8, 15, 20, 25, 30);
	matrix.m_large = Fzzy::Fuzzifier::FuzzyGrade(8, 25, 30);
	matrix.m_close = Fzzy::Fuzzifier::FuzzyTriangle(25, -30, 0, 30);
	matrix.m_mediumDistance = Fzzy::Fuzzifier::FuzzyTrapezoid(25, 10, 30, 50, 70);
	matrix.m_far = Fzzy::Fuzzifier::FuzzyGrade(25, 50, 70);
	matrix.m_low = Fzzy::LogicalOperators::FuzzyOr(Fzzy::LogicalOperators::FuzzyAnd(matrix.m_mediumDistance, matrix.m_tiny),
		Fzzy::LogicalOperators::FuzzyAnd(matrix.m_mediumDistance, matrix.m_small));
	matrix.m_medium = Fzzy::LogicalOperators::FuzzyAnd(matrix.m_close, matrix.m_tiny);
	matrix.m_high = Fzzy::LogicalOperators::FuzzyAnd(matrix.m_close, Fzzy::LogicalOperators::FuzzyNot(matrix.m_mediumDistance));
}

double Fzzy::Fuzzifier::DefuzzifyRuleMatrix(const ruleMatrix& matrix)
{
	return (matrix.m_low * 10 + matrix.m_medium * 30 + matrix.m_high * 50) / (matrix.m_low + matrix.m_medium + matrix.m_high);
}

double Fzzy::Fuzzifier::FuzzyGrade(double value, double x0, double x1)
{
	if (value < x0) return 0;
	if (value > x1) return 1;
	return (value - x0) / (x1 - x0);
}

double Fzzy::Fuzzifier::FuzzyTriangle(double value, double x0, double x1, double x2)
{
	if (value <= x0 || value >= x2) return 0;
	if (value == x1) return 1; 
	if(value > x0 && value < x1) return (value - x0) / (x1 - x0);
	return (x2 - value) / (x2 - x1);
}

double Fzzy::Fuzzifier::FuzzyTrapezoid(double value, double x0, double x1, double x2, double x3)
{
	if(value <= x0 || value >= x3) return 0;
	if (value >= x1 && value <= x2) return 1;
	if (value > x0 && value < x1) return (value - x0) / (x1 - x0);
	return (x3 - value) / (x3 - x2);
}
