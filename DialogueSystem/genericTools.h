#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

extern sf::Font font;

namespace DialogueTools 
{
	std::vector<std::string> ImportText(std::filesystem::path file);
}

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