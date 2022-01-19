#ifndef FUZZY_H
#define FUZZY_H

#include <algorithm>

class Fuzzy
{
public:
	Fuzzy() {};

	double FuzzyGrade(double t_value, double t_x0, double t_x1);
	double FuzzyTriangle(double t_value, double t_x0, double t_x1, double t_x2);
	double fuzzyTrapezoid(double t_value, double t_x0, double t_x1, double t_x2);

	double FuzzyAND(double t_a, double t_b);
	double FuzzyOR(double t_a, double t_b);
	double FuzzyNOT(double t_a);

};

#endif // !FUZZY_H

