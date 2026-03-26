#pragma once
#include "Include.h"

class History
{
private:
	const int historySpacing = 100;

	sf::RectangleShape Background = sf::RectangleShape();
	sf::Text prompt = sf::Text(font, "[TAB] view History", 20);
	sf::Text header = sf::Text(font, "History", 100);

public:
	std::vector<sf::Text> items = std::vector<sf::Text>();

	History() = default;
	void Draw(sf::RenderWindow& window);
	void ButtonPrompt(sf::RenderWindow& window);
};

