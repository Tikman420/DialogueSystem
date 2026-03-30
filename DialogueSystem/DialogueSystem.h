#pragma once
#include "Include.h"
#include "RichText.h"
#include "History.h"
#include "Profile.h"

extern sf::Font font;
extern std::string Images;

namespace DialogueTools
{
    //std::vector<std::string> ImportText(std::string file);

    class DialogueSystem
    {
    private:
        const float blink = 2;
        const float blinkLength = 0.15;
        const int characterPerTalk = 3;

        //background settings
        sf::Color backgroundColor = sf::Color(0, 0, 0, 240);
        const sf::Vector2f defaultPosition = sf::Vector2f(960, 892);
        const sf::Vector2f defaultSize = sf::Vector2f(1410, 382);

        //other stuff not changable
        float blinkTimer = 0;
        float blinkStayTimer = 0;
        int currentChar = 0;
        sf::RectangleShape mainWindow = sf::RectangleShape(backGroundSize);
        Profile profile = Profile(Images + "ProfilesPlaceHolder.png", defaultPosition + sf::Vector2f(-510, 0));
        sf::Text dialogueText = sf::Text(font);

    public:
        sf::Vector2f backGroundPosition;
        sf::Vector2f backGroundSize;
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