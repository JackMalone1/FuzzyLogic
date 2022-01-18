#pragma once
#include "FzzyLogic.h"
namespace Fzzy
{
	namespace Fuzzifier
	{
		struct ruleMatrix
		{
			double m_tiny;
			double m_small;
			double m_moderate;
			double m_large;
			double m_close;
			double m_mediumDistance;
			double m_far;
			double m_low;
			double m_medium;
			double m_high;
			double m_deploy;
		};

		void SetUpRuleMatrix(ruleMatrix& matrix);
		double DefuzzifyRuleMatrix(const ruleMatrix& matrix);
		double FuzzyGrade(double value, double x0, double x1);
		double FuzzyTriangle(double value, double x0, double x1, double x2);
		double FuzzyTrapezoid(double value, double x0, double x1, double x2, double x3);
	}
}