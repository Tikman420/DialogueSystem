#include "genericTools.h"

//fps counter stuff
sf::Clock fpsTimer;
sf::Text fpsCounter(font);
float deltaTime;

void Tools::UpdateDeltaTime()
{
	deltaTime = fpsTimer.getElapsedTime().asSeconds();

    //set fps counter
    fpsTimer.restart();
    int fps = 1 / deltaTime;
    fpsCounter.setString(std::to_string(fps) + " FPS");
    fpsCounter.setFillColor(sf::Color(0,0,0,255));
    //fpsCounter.setPosition(sf::Vector2f(window.getSize().x - fpsCounter.getGlobalBounds().size.x - uiPadding.x, uiPadding.y));
}

float Tools::GetDeltaTime()
{
	return deltaTime;
}

void Tools::RenderFPS(sf::RenderWindow& window)
{
    window.draw(fpsCounter);
}
