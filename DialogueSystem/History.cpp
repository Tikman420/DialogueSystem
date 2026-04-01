#include "History.h"

void History::Draw(sf::RenderWindow& window) 
{
	//initializer
	if (Background.getSize() == sf::Vector2f(0,0))
	{
		Background.setSize(sf::Vector2f(window.getSize()));
		Background.setFillColor(sf::Color(0,0,0, 200));

		header.setOrigin(header.getLocalBounds().size/(float)2);
		header.setPosition(sf::Vector2f(window.getSize().x/2, 50));
	}

	//draw the background and the header
	window.draw(Background);
	window.draw(header);

	//draw the text from history if it's under a certain position
	int amount = 1;
	for (int i = items.size()-1; i != -1; i--) 
	{
		auto textPosition = sf::Vector2f(window.getSize().x / 2, window.getSize().y - historySpacing * amount);

		if (textPosition.y <= header.getPosition().y + header.getCharacterSize())
		{
			break;
		}
		items[i].setOrigin(items[i].getLocalBounds().size / (float)2);
		items[i].setPosition(textPosition);
		window.draw(items[i]);
		amount++;
	}
}

//draw button prompt
void History::ButtonPrompt(sf::RenderWindow& window)
{
	prompt.setFillColor(sf::Color(0, 0, 0, 255));
	prompt.setPosition(sf::Vector2f(prompt.getCharacterSize(), window.getSize().y - prompt.getCharacterSize() * 2));
	prompt.setStyle(sf::Text::Bold);
	window.draw(prompt);
}
	