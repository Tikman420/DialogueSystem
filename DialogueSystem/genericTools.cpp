#include "genericTools.h"

//fps counter stuff
sf::Clock fpsTimer;
sf::Text fpsCounter(font);
float deltaTime;

//import a file based on lines
//returns: vector with every line of text
std::vector<std::string> DialogueTools::ImportText(const std::filesystem::path& file)
{
    //UwU: impwementot

    //setup for variables
    std::vector<std::string> result;
    std::ifstream source = std::ifstream(file, std::ios::ate);

    //get size of file
    int size = source.tellg();
    source.seekg(0);

    //load the text into the vector
    std::string str;
    //https://stackoverflow.com/questions/13035674/how-to-read-a-file-line-by-line-or-a-whole-text-file-at-once
    while (std::getline(source, str))
    {
        result.emplace_back(str);
    }

    //close file
    source.close();

    return result;
}

void Tools::UpdateDeltaTime()
{
    //get the elapsed time from the timer
	deltaTime = fpsTimer.getElapsedTime().asSeconds();

    //set fps counter
    fpsTimer.restart();
    int fps = 1 / deltaTime;
    fpsCounter.setString(std::to_string(fps) + " FPS");
    fpsCounter.setFillColor(sf::Color(0,0,0,255));
    //fpsCounter.setPosition(sf::Vector2f(window.getSize().x - fpsCounter.getGlobalBounds().size.x - uiPadding.x, uiPadding.y));
}

const float Tools::GetDeltaTime()
{
	return deltaTime;
}

void Tools::RenderFPS(sf::RenderWindow& window)
{
    window.draw(fpsCounter);
}
