#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif

#include <iostream>
#include "Game.h"
#include "Fuzzy.h"

int main()
{
	//Game game;
	//game.run();

	Fuzzy m_fuzzyLogic;

	double m_troops = 8.0;
	double m_range = 25.0;

	double m_tinyForce = m_fuzzyLogic.FuzzyTriangle(m_troops, -10.0, 0.0, 10.0);
	double m_smallForce = m_fuzzyLogic.FuzzyTrapezoid(m_troops, 2.5, 10.0, 15.0, 20.0);
	double m_mediumForce = m_fuzzyLogic.FuzzyTrapezoid(m_troops,15.0,20.0,25.0,30.0);
	double m_largeForce = m_fuzzyLogic.FuzzyGrade(m_troops,25.0,30.0);

	double m_close = m_fuzzyLogic.FuzzyTriangle(m_range,-30.0,0.0,30.0);
	double m_medium = m_fuzzyLogic.FuzzyTrapezoid(m_range,10.0,30.0,50.0,70.0);
	double m_far = m_fuzzyLogic.FuzzyGrade(m_range,50.0,70.0);

	double m_lowThreat = m_fuzzyLogic.FuzzyOR(m_fuzzyLogic.FuzzyAND(m_medium, m_tinyForce), m_fuzzyLogic.FuzzyAND(m_medium, m_smallForce));
	double m_mediumThreat = m_fuzzyLogic.FuzzyAND(m_close,m_tinyForce);
	double m_highThreat = m_fuzzyLogic.FuzzyAND(m_close,m_fuzzyLogic.FuzzyNOT(m_medium));

	double m_deploy = (m_lowThreat * 10.0 + m_mediumThreat * 30.0 + m_highThreat * 50.0) / (m_lowThreat + m_mediumThreat + m_highThreat);

	std::cout << m_troops << " Enemy troops, Spotted at the distances of " << m_range << std::endl;
	std::cout << "Deploying Reinforcement size of " << m_deploy << " Troops" << std::endl;



	system("pause");

	return EXIT_SUCCESS;
}