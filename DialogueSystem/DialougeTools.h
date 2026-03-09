#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <vector>

extern sf::Font font;
extern std::string Images;

namespace DialogueTools
{
    class DialogueSystem
    {
    private:
        //change dialogue settings here
        sf::Color backgroundColor = sf::Color(0,0,0,240);
        const sf::Vector2f defaultPosition = sf::Vector2f(960, 892);
        const sf::Vector2f defaultSize = sf::Vector2f(1410, 382);

        sf::RectangleShape mainWindow = sf::RectangleShape(backGroundSize);
        sf::Texture* profileTexture = new sf::Texture(Images + "ProfilesPlaceHolder.png");
        sf::Sprite profile = sf::Sprite(*profileTexture, sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(228, 228)));
        sf::Text dialogueText = sf::Text(font);

    public:
        sf::Vector2f backGroundPosition;
        sf::Vector2f backGroundSize;
        int currentDialogue;
        bool inDialogue = false;

        std::string dialogueName = std::string();
        std::vector<std::string>* dialogueBuffer = new std::vector<std::string>();

        DialogueSystem();
        void Draw(sf::RenderWindow& window);
        const void resetTransform();

        //dialogue control
        void ProcessEvent(const sf::RenderWindow& window, const sf::Event& event);
        void initDialogue(std::string dialogueName);
        void StartDialogue(int index);
        void NextDialogue();
    };

    static ImGuiWindowFlags Dialogueflags { ImGuiWindowFlags_MenuBar };

    void ShowDebugMenu(DialogueSystem& system, sf::RenderWindow& window);
    void ShowFileMenu();
    void ShowEditMenu();
    void ImportText();

}

namespace sf 
{
    float** Vec2ToFloat(Vector2f& origin);
}