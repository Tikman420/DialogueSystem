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
        //background settings
        sf::Color backgroundColor = sf::Color(0,0,0,240);
        const sf::Vector2f defaultPosition = sf::Vector2f(960, 892);
        const sf::Vector2f defaultSize = sf::Vector2f(1410, 382);

        //TypeWriter settings (not implemented yet)
        const sf::Time normalDelay = sf::milliseconds(123);
        const sf::Time PunctuationDelay = sf::milliseconds(235);

        int WrappingCount = 40; //in pixels

        //other stuff not changable
        sf::RectangleShape mainWindow = sf::RectangleShape(backGroundSize);
        sf::Texture* profileTexture = new sf::Texture(Images + "ProfilesPlaceHolder.png");
        sf::Sprite profile = sf::Sprite(*profileTexture, sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(228, 228)));
        sf::Text dialogueText = sf::Text(font);
        
        //typewriter stuff
        sf::Clock typewriterTimer;

    public:
        sf::Vector2f backGroundPosition;
        sf::Vector2f backGroundSize;
        int currentDialogue;

        std::string currentDialogueName = std::string();
        std::vector<std::string>* dialogueBuffer = new std::vector<std::string>();

        DialogueSystem();
        void Draw(sf::RenderWindow& window);
        const void resetTransform();

        //text handling
        void RenderText(sf::Text& dialogueBox, std::string text);
        static void WordWrapping(std::string& text, int wrapLength);

        //dialogue control
        void ProcessEvent(const sf::RenderWindow& window, const sf::Event& event);
        void InitDialogue(std::string dialogueName);
        void StartDialogue(int index);
        void NextDialogue();
    };

    static ImGuiWindowFlags Dialogueflags { ImGuiWindowFlags_MenuBar };

    void ShowDebugMenu(DialogueSystem& system, sf::RenderWindow& window);
    void ShowFileMenu();
    void ShowEditMenu();
    std::vector<std::string> ImportText(std::string file);

}

namespace sf 
{
    float** Vec2ToFloat(Vector2f& origin);
}