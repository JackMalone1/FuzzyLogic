#include "FzzyFuzzifier.h"

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
