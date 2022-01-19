#include "FzzyFuzzifier.h"

void Fzzy::Fuzzifier::SetUpRuleMatrix(ruleMatrix& matrix)
{
	matrix.m_tinyForce = Fzzy::Fuzzifier::FuzzyTriangle(matrix.m_tiny);
	matrix.m_smallForce = Fzzy::Fuzzifier::FuzzyTrapezoid(matrix.m_small);
	matrix.m_moderateForce = Fzzy::Fuzzifier::FuzzyTrapezoid(matrix.m_moderate);
	matrix.m_largeForce = Fzzy::Fuzzifier::FuzzyGrade(matrix.m_large);
	matrix.m_closeDistance = Fzzy::Fuzzifier::FuzzyTriangle(matrix.m_close);
	matrix.m_mediumDistance = Fzzy::Fuzzifier::FuzzyTrapezoid(matrix.m_medium);
	matrix.m_farDistance = Fzzy::Fuzzifier::FuzzyGrade(matrix.m_far);
	matrix.m_lowAssessment = Fzzy::LogicalOperators::FuzzyOr(Fzzy::LogicalOperators::FuzzyAnd(matrix.m_mediumDistance, matrix.m_tinyForce),
		Fzzy::LogicalOperators::FuzzyAnd(matrix.m_mediumDistance, matrix.m_smallForce));
	matrix.m_mediumAssessment = Fzzy::LogicalOperators::FuzzyAnd(matrix.m_closeDistance, matrix.m_tinyForce);
	matrix.m_highAssessment = Fzzy::LogicalOperators::FuzzyAnd(matrix.m_closeDistance, Fzzy::LogicalOperators::FuzzyNot(matrix.m_mediumDistance));
}

double Fzzy::Fuzzifier::DefuzzifyRuleMatrix(const ruleMatrix& matrix)
{
	return (matrix.m_lowAssessment * 10 + matrix.m_mediumAssessment * 30 + matrix.m_highAssessment * 50) / (matrix.m_lowAssessment + matrix.m_mediumAssessment + matrix.m_highAssessment);
}

double Fzzy::Fuzzifier::FuzzyGrade(const grade& grade)
{
	if (grade.value < grade.x0) return 0;
	if (grade.value > grade.x1) return 1;
	return (grade.value - grade.x0) / (grade.x1 - grade.x0);
}

double Fzzy::Fuzzifier::FuzzyTriangle(const triangle& triangle)
{
	if (triangle.value <= triangle.x0 || triangle.value >= triangle.x2) return 0;
	if (triangle.value == triangle.x1) return 1;
	if(triangle.value > triangle.x0 && triangle.value < triangle.x1) return (triangle.value - triangle.x0) / (triangle.x1 - triangle.x0);
	return (triangle.x2 - triangle.value) / (triangle.x2 - triangle.x1);
}

double Fzzy::Fuzzifier::FuzzyTrapezoid(const trapezoid& trapezoid)
{
	if(trapezoid.value <= trapezoid.x0 || trapezoid.value >= trapezoid.x3) return 0;
	if (trapezoid.value >= trapezoid.x1 && trapezoid.value <= trapezoid.x2) return 1;
	if (trapezoid.value > trapezoid.x0 && trapezoid.value < trapezoid.x1) return (trapezoid.value - trapezoid.x0) / (trapezoid.x1 - trapezoid.x0);
	return (trapezoid.x3 - trapezoid.value) / (trapezoid.x3 - trapezoid.x2);
}
