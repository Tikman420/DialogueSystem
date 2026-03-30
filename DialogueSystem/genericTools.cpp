#include "genericTools.h"

//fps counter stuff
sf::Clock fpsTimer;
sf::Text fpsCounter(font);
float deltaTime;


std::vector<std::string> DialogueTools::ImportText(std::filesystem::path file)
{
    //UwU: impwementot
    std::vector<std::string> result;
    std::ifstream source = std::ifstream(file, std::ios::ate);

    int size = source.tellg();
    source.seekg(0);

    std::string str;
    //https://stackoverflow.com/questions/13035674/how-to-read-a-file-line-by-line-or-a-whole-text-file-at-once
    while (std::getline(source, str))
    {
        std::cout << str << std::endl;
        result.emplace_back(str);
    }

    return result;
}

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
