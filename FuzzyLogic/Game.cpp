#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 1000U, 600U, 32U }, "SFML Game" },
	m_exitGame{ false }, m_dividingLine{sf::Lines, 2}
{
	if (!m_font.loadFromFile("assets//fonts//MONOFONT.ttf"))
	{
		std::cerr << "Unable to load font" << std::endl;
		throw std::exception("File not found");
	}

	if (!m_texture.loadFromFile("assets//images//background.jpg"))
	{
		std::cerr << "Unable to load background" << std::endl;
		throw std::exception("File not found");
	}

	m_background.setTexture(m_texture);

	m_numberOfFriendlies.setFont(m_font);
	m_numberOfFriendlies.setCharacterSize(18);
	m_numberOfFriendlies.setPosition(sf::Vector2f(100, 50));
	m_numberOfFriendlies.setFillColor(sf::Color::Black);

	m_numberOfEnemies.setFont(m_font);
	m_numberOfEnemies.setCharacterSize(18);
	m_numberOfEnemies.setPosition(sf::Vector2f(300, 50));
	m_numberOfEnemies.setFillColor(sf::Color::Black);

	m_distanceAwayOfEnemies.setFont(m_font);
	m_distanceAwayOfEnemies.setCharacterSize(18);
	m_distanceAwayOfEnemies.setPosition(sf::Vector2f(500, 50));
	m_distanceAwayOfEnemies.setFillColor(sf::Color::Black);

	m_textBackground.setSize(sf::Vector2f(625, 75));
	m_textBackground.setPosition(m_numberOfFriendlies.getPosition() - sf::Vector2f(25, 25));
	m_textBackground.setFillColor(sf::Color(211, 211, 211, 125));
	m_dividingLine.append(sf::Vertex(sf::Vector2f(100, 0), sf::Color::Black));
	m_dividingLine.append(sf::Vertex(sf::Vector2f(100, 600), sf::Color::Black));

	m_guide.setFont(m_font);
	m_guide.setCharacterSize(18);
	m_guide.setPosition(sf::Vector2f(800, 50));
	m_guide.setFillColor(sf::Color::Black);
	m_guide.setString("Press Enter to reset");
	m_guideBackground.setSize(sf::Vector2f(200, 75));
	m_guideBackground.setPosition(m_guide.getPosition() - sf::Vector2f(15, 25));
	m_guideBackground.setFillColor(sf::Color(211, 211, 211, 125));
	setUpEnemies();
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

	if (sf::Keyboard::Enter == t_event.key.code)
	{
		setUpMatrix();
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
	m_window.draw(m_background);

	for (auto& friendly : m_friendlies)
	{
		m_window.draw(friendly);
	}

	for (auto& enemy : m_enemies)
	{
		m_window.draw(enemy);
	}
	m_window.draw(m_textBackground);
	m_window.draw(m_numberOfFriendlies);
	m_window.draw(m_numberOfEnemies);
	m_window.draw(m_distanceAwayOfEnemies);
	m_window.draw(m_guideBackground);
	m_window.draw(m_guide);
	m_window.draw(m_dividingLine);
	m_window.display();
}

void Game::setUpEnemies()
{
	setUpMatrix();
}

void Game::setUpMatrix()
{
	numberOfEnemies = rand() % 30 + 1;
	distanceAwayOfEnemies = rand() % 65 + 10;
	Fzzy::Fuzzifier::ruleMatrix ruleMatrix;
	Fzzy::Fuzzifier::triangle tri;
	tri.value = numberOfEnemies;
	tri.x0 = -10;
	tri.x1 = 0;
	tri.x2 = 10;
	ruleMatrix.m_tiny = tri;
	Fzzy::Fuzzifier::trapezoid trap;
	trap.value = numberOfEnemies;
	trap.x0 = 2.5;
	trap.x1 = 10;
	trap.x2 = 15;
	trap.x3 = 20;
	ruleMatrix.m_small = trap;
	trap.value = numberOfEnemies;
	trap.x0 = 15;
	trap.x1 = 20;
	trap.x2 = 25;
	trap.x3 = 30;
	ruleMatrix.m_moderate = trap;
	Fzzy::Fuzzifier::grade gr;
	gr.value = numberOfEnemies;
	gr.x0 = 25;
	gr.x1 = 30;
	ruleMatrix.m_large = gr;
	tri.value = distanceAwayOfEnemies;
	tri.x0 = -30;
	tri.x1 = 0;
	tri.x2 = 30;
	ruleMatrix.m_close = tri;
	trap.value = distanceAwayOfEnemies;
	trap.x0 = 10;
	trap.x1 = 30;
	trap.x2 = 50;
	trap.x3 = 70;
	ruleMatrix.m_medium = trap;
	gr.value = distanceAwayOfEnemies;
	gr.x0 = 50;
	gr.x1 = 70;
	ruleMatrix.m_far = gr;
	Fzzy::Fuzzifier::SetUpRuleMatrix(ruleMatrix);
	m_deploy = std::ceil(Fzzy::Fuzzifier::DefuzzifyRuleMatrix(ruleMatrix));
	m_numberOfFriendlies.setString("Number of friendlies: " + std::to_string(m_deploy));
	m_numberOfEnemies.setString("Number of enemies: " + std::to_string(numberOfEnemies));
	m_distanceAwayOfEnemies.setString("Distance from Enemies: " + std::to_string(distanceAwayOfEnemies));
	setUpDisplay();
}

void Game::setUpDisplay()
{
	m_friendlies.clear();
	m_enemies.clear();

	for (size_t i = 0; i < m_deploy; ++i)
	{
		int x = rand() % 90 + 4;
		int y = rand() % 590 + 4;
		sf::CircleShape shape;
		shape.setRadius(5);
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color::Blue);
		m_friendlies.push_back(shape);
	}

	for (size_t i = 0; i < numberOfEnemies; ++i)
	{
		int x = rand() % 200 + (distanceAwayOfEnemies * 10);
		int y = rand() % 590 + 4;
		sf::CircleShape shape;
		shape.setRadius(5);
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color::Red);
		m_enemies.push_back(shape);
	}
}

