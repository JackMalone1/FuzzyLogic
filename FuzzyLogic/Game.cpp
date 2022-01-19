#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{ false }
{
	int enemySize = rand() % 8 + 1;
	int distance = rand() % 65 + 10;
	Fzzy::Fuzzifier::ruleMatrix ruleMatrix;
	Fzzy::Fuzzifier::triangle tri;
	tri.value = enemySize;
	tri.x0 = -10;
	tri.x1 = 0;
	tri.x2 = 10;
	ruleMatrix.m_tiny = tri;
	Fzzy::Fuzzifier::trapezoid trap;
	trap.value = enemySize;
	trap.x0 = 2.5;
	trap.x1 = 10;
	trap.x2 = 15;
	trap.x3 = 20;
	ruleMatrix.m_small = trap;
	trap.value = enemySize;
	trap.x0 = 15;
	trap.x1 = 20;
	trap.x2 = 25;
	trap.x3 = 30;
	ruleMatrix.m_moderate = trap;
	Fzzy::Fuzzifier::grade gr;
	gr.value = enemySize;
	gr.x0 = 25;
	gr.x1 = 30;
	ruleMatrix.m_large = gr;
	tri.value = distance;
	tri.x0 = -30;
	tri.x1 = 0;
	tri.x2 = 30;
	ruleMatrix.m_close = tri;
	trap.value = distance;
	trap.x0 = 10;
	trap.x1 = 30;
	trap.x2 = 50;
	trap.x3 = 70;
	ruleMatrix.m_medium = trap;
	gr.value = distance;
	gr.x0 = 50;
	gr.x1 = 70;
	ruleMatrix.m_far = gr;
	Fzzy::Fuzzifier::SetUpRuleMatrix(ruleMatrix);
	m_deploy = Fzzy::Fuzzifier::DefuzzifyRuleMatrix(ruleMatrix);
	std::cout << m_deploy << std::endl;
}


Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps);
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); 
			update(timePerFrame); 
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) 
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) 
		{
			processKeys(newEvent);
		}
	}
}



void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}


void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}


void Game::render()
{
	m_window.clear(sf::Color::White);

	m_window.display();
}

