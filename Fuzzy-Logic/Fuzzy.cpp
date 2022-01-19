#include "Fuzzy.h"

double Fuzzy::FuzzyGrade(double t_value, double t_x0, double t_x1)
{
    double m_result = 0;
    double m_x = t_value;

    if (m_x <= t_x0)
        m_result = 0;
    else if (m_x > t_x1)
        m_result = 1;
    else
        m_result = ((m_x - t_x0) / (t_x1 - t_x0));
    return m_result;
}

double Fuzzy::FuzzyTriangle(double t_value, double t_x0, double t_x1, double t_x2)
{
    double m_result = 0;
    double m_x = t_value;

    if ((m_x <= t_x0) || (m_x >= t_x2))
        m_result = 0;
    else if (m_x == t_x1)
        m_result = 1;
    else if ((m_x > t_x0) && (m_x < t_x1))
        m_result = ((m_x - t_x0) / (t_x1 - t_x0));
    else
        m_result = ((t_x2 - m_x) / (t_x2 - t_x1));
    return m_result;
}

double Fuzzy::FuzzyTrapezoid(double t_value, double t_x0, double t_x1, double t_x2, double t_x3)
{
    double m_result = 0;
    double m_x = t_value;

    if ((m_x <= t_x0) || (m_x >= t_x3))
        m_result = 0;
    else if ((m_x >= t_x1) && (m_x <= t_x2))
        m_result = 1;
    else if ((m_x > t_x0) && (m_x < t_x1))
        m_result = ((m_x - t_x0) / (t_x1 - t_x0));
    else
        m_result = ((t_x3 - m_x) / (t_x3 - t_x2));
    return m_result;
}

double Fuzzy::FuzzyAND(double t_a, double t_b)
{
    return std::min(t_a, t_b);
}

double Fuzzy::FuzzyOR(double t_a, double t_b)
{
    return std::max(t_a, t_b);
}

double Fuzzy::FuzzyNOT(double t_a)
{
    return 1.0 - t_a;
}
