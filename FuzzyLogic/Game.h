#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Fzzy.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void setUpEnemies();
	void setUpMatrix();

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
	sf::RenderWindow m_window;

	bool m_exitGame;

};

#endif 