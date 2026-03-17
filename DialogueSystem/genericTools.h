#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

extern sf::Font font;

namespace Tools 
{
	void UpdateDeltaTime();
	float GetDeltaTime();
	void RenderFPS(sf::RenderWindow& window);
}

namespace sf
{
	float** Vec2ToFloat(Vector2f& origin);
}