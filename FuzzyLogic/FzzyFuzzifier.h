#pragma once
#include "FzzyLogic.h"
namespace Fzzy
{
	namespace Fuzzifier
	{
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
		};

		void SetUpRuleMatrix(ruleMatrix& matrix);
		double DefuzzifyRuleMatrix(const ruleMatrix& matrix);
		double FuzzyGrade(double value, double x0, double x1);
		double FuzzyTriangle(double value, double x0, double x1, double x2);
		double FuzzyTrapezoid(double value, double x0, double x1, double x2, double x3);
	}
}