#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

extern sf::Font font;

namespace DialogueTools 
{
	//import a file based on lines
	std::vector<std::string> ImportText(const std::filesystem::path& file);
}

namespace Tools 
{
	//deltatime / fps counter stuff
	void UpdateDeltaTime();
	const float GetDeltaTime();
	void RenderFPS(sf::RenderWindow& window);
}

namespace sf
{
	//conversion from vector2 to float array
	float** Vec2ToFloat(Vector2f& origin);
}