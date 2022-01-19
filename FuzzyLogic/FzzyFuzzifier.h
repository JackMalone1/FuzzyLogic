#pragma once
#include "FzzyLogic.h"
namespace Fzzy
{
	namespace Fuzzifier
	{
		struct grade
		{
			double value;
			double x0;
			double x1;
		};

		struct triangle
		{
			double value;
			double x0;
			double x1;
			double x2;
		};

		struct trapezoid
		{
			double value;
			double x0;
			double x1;
			double x2;
			double x3;
		};

		struct ruleMatrix
		{
			double m_tinyForce;
			double m_smallForce;
			double m_moderateForce;
			double m_largeForce;
			double m_closeDistance;
			double m_mediumDistance;
			double m_farDistance;
			double m_lowAssessment;
			double m_mediumAssessment;
			double m_highAssessment;
			double m_deploy;
			triangle m_tiny;
			trapezoid m_small;
			trapezoid m_moderate;
			grade m_large;
			triangle m_close;
			trapezoid m_medium;
			grade m_far;
		};

		 void SetUpRuleMatrix(ruleMatrix& matrix);
		 double DefuzzifyRuleMatrix(const ruleMatrix& matrix);
		 double FuzzyGrade(const grade& grade);
		 double FuzzyTriangle(const triangle& triangle);
		 double FuzzyTrapezoid(const trapezoid& trapezoid);
	}
}