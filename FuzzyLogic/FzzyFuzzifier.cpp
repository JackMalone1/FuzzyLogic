#include "FzzyFuzzifier.h"

void Fzzy::Fuzzifier::SetUpRuleMatrix(ruleMatrix& matrix)
{
	matrix.m_tinyForce = Fzzy::Fuzzifier::FuzzyTriangle(8, -10, 0, 10);
	matrix.m_smallForce = Fzzy::Fuzzifier::FuzzyTrapezoid(8, 2.5, 10, 15, 20);
	matrix.m_moderateForce = Fzzy::Fuzzifier::FuzzyTrapezoid(8, 15, 20, 25, 30);
	matrix.m_largeForce = Fzzy::Fuzzifier::FuzzyGrade(8, 25, 30);
	matrix.m_closeDistance = Fzzy::Fuzzifier::FuzzyTriangle(25, -30, 0, 30);
	matrix.m_mediumDistance = Fzzy::Fuzzifier::FuzzyTrapezoid(25, 10, 30, 50, 70);
	matrix.m_farDistance = Fzzy::Fuzzifier::FuzzyGrade(25, 50, 70);
	matrix.m_lowAssessment = Fzzy::LogicalOperators::FuzzyOr(Fzzy::LogicalOperators::FuzzyAnd(matrix.m_mediumDistance, matrix.m_tinyForce),
		Fzzy::LogicalOperators::FuzzyAnd(matrix.m_mediumDistance, matrix.m_smallForce));
	matrix.m_mediumAssessment = Fzzy::LogicalOperators::FuzzyAnd(matrix.m_closeDistance, matrix.m_tinyForce);
	matrix.m_highAssessment = Fzzy::LogicalOperators::FuzzyAnd(matrix.m_closeDistance, Fzzy::LogicalOperators::FuzzyNot(matrix.m_mediumDistance));
}

double Fzzy::Fuzzifier::DefuzzifyRuleMatrix(const ruleMatrix& matrix)
{
	return (matrix.m_lowAssessment * 10 + matrix.m_mediumAssessment * 30 + matrix.m_highAssessment * 50) / (matrix.m_lowAssessment + matrix.m_mediumAssessment + matrix.m_highAssessment);
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
