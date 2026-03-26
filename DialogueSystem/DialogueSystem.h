#pragma once
#include "Include.h"
#include "RichText.h"

extern sf::Font font;
extern std::string Images;

namespace DialogueTools
{
    std::vector<std::string> ImportText(std::string file);

    class DialogueSystem
    {
    private:
        //background settings
        sf::Color backgroundColor = sf::Color(0, 0, 0, 240);
        const sf::Vector2f defaultPosition = sf::Vector2f(960, 892);
        const sf::Vector2f defaultSize = sf::Vector2f(1410, 382);

        //other stuff not changable
        sf::RectangleShape mainWindow = sf::RectangleShape(backGroundSize);
        sf::Texture* profileTexture = new sf::Texture(Images + "ProfilesPlaceHolder.png");
        sf::Sprite profile = sf::Sprite(*profileTexture, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(228, 228)));
        sf::Text dialogueText = sf::Text(font);

    public:
        sf::Vector2f backGroundPosition;
        sf::Vector2f backGroundSize;
        int currentDialogue;

        std::string currentDialogueName = std::string();
        std::vector<std::string>* dialogueBuffer = new std::vector<std::string>();
        std::vector<sf::Text>* History = new std::vector<sf::Text>();
        RichText dialogueTexts;

        DialogueSystem();
        ~DialogueSystem();
        void Draw(sf::RenderWindow& window);
        const void resetTransform();

        //dialogue control
        void ProcessEvent(const sf::RenderWindow& window, const sf::Event& event);
        void InitDialogue(std::string dialogueName);
        void StartDialogue(int index);
        void NextDialogue();
    };
}