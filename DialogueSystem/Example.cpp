#include "Include.h"

#include "DialogueTools.h"
#include "DialogueSystem.h"

std::string Images = "Game/Images/";
sf::Font font = sf::Font("Game/Fonts/Roboto-Regular.ttf");

bool showCollision;

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Dialogue Test", sf::Style::None);
    if (!ImGui::SFML::Init(window)) 
    {
        return -1;
    }

    DialogueTools::DialogueSystem dialogue;

    std::string dialogueName = std::string();
    std::vector<std::string>* dialogueBuffer = new std::vector<std::string>();
    dialogueBuffer->push_back("Hello World!");

    sf::CircleShape shape(100.0f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;

    dialogue.InitDialogue("Test");
    while (window.isOpen()) 
    {
        while (const auto event = window.pollEvent()) 
        {
            ImGui::SFML::ProcessEvent(window, *event);
            dialogue.ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
            {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        //show imgui's feature showcase window
        ImGui::ShowDemoWindow();

        //show own menu
        DialogueTools::ShowDebugMenu(dialogue, window);
        ImGui::End();

        window.clear(sf::Color(255,255,255));
        window.draw(shape);
        if (dialogue.currentDialogueName != "") 
        {
            dialogue.Draw(window);
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

float** sf::Vec2ToFloat(sf::Vector2f& origin)
{
    return new float*[2]{ &origin.x, &origin.y };
}