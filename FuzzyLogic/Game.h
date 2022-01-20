#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Fzzy.h"
#include <vector>


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

	void setUpDisplay();

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
	int m_deploy;
	sf::RenderWindow m_window;
	int numberOfEnemies;
	int distanceAwayOfEnemies;
	bool m_exitGame;

	sf::Text m_numberOfFriendlies;
	sf::Text m_numberOfEnemies;
	sf::Text m_distanceAwayOfEnemies;

	sf::Text m_guide;
	sf::RectangleShape m_guideBackground;

	sf::RectangleShape m_textBackground;
	sf::Font m_font;

	sf::Sprite m_background;
	sf::Texture m_texture;

	std::vector<sf::CircleShape> m_friendlies;
	std::vector<sf::CircleShape> m_enemies;

	sf::VertexArray m_dividingLine;
};

#endif 