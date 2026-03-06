#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <imgui-SFML.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>

#include "DialougeTools.h"

std::string Images = "Game/Images/";
sf::Font font = sf::Font("Game/Fonts/Roboto-Regular.ttf");

bool showCollision;

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1000, 700 }), "Dialogue Test", sf::Style::Close);
    if (!ImGui::SFML::Init(window)) 
    {
        return -1;
    }

    DialogueTools::DialogueSystem dialogue = DialogueTools::DialogueSystem(sf::Vector2f(), sf::Vector2f(1,1), "");

    std::string dialogueName = std::string();
    std::vector<std::string>* dialogueBuffer = new std::vector<std::string>();
    dialogueBuffer->push_back("Hello World!");

    sf::CircleShape shape(100.0f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;
    while (window.isOpen()) 
    {
        while (const auto event = window.pollEvent()) 
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) 
            {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::ShowDemoWindow();

        DialogueTools::ShowDebugMenu(dialogueName, dialogueBuffer);

        window.clear(sf::Color(255,255,255));
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}