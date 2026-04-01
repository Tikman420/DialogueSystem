#pragma once
#include "Include.h"
#include "RichText.h"
#include "History.h"
#include "profile.h"

extern sf::Font font;
extern std::string Images;

namespace DialogueTools
{
    //class that connects all the dialogueclasses
    class DialogueSystem
    {
    private:
        //profiles animation variables
        const float blink = 2;
        const float blinkLength = 0.15;
        const int characterPerTalk = 2;

        //background settings
        sf::Color backgroundColor = sf::Color(0, 0, 0, 240);
        const sf::Vector2f Position = sf::Vector2f(960, 892);
        const sf::Vector2f Size = sf::Vector2f(1410, 382);

        //other stuff not changable
        float blinkTimer = 0;
        float blinkStayTimer = 0;
        int currentChar = 0;
        sf::RectangleShape mainWindow = sf::RectangleShape(Size);
        std::vector<Profile> profiles = { Profile(Images + "profilesPlaceHolder.png"), Profile(Images + "2ndcharacter.png") };
        sf::Text dialogueText = sf::Text(font);

        const sf::Vector2f namePosition = sf::Vector2f(255, 641);
        const sf::Vector2f nameSize = sf::Vector2f(466, 60);
        const sf::Vector2f padding = sf::Vector2f(15,10);
        sf::RectangleShape nameWindow = sf::RectangleShape();
        sf::Text name = sf::Text(font, "NAME", 40);

    public:
        int currentDialogue;
        std::string currentEmotion = "neutral";

        std::string currentDialogueName = std::string();
        std::vector<std::string>* dialogueBuffer = new std::vector<std::string>();
        History* history = new History();
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