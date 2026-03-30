#include "DialogueSystem.h"

namespace DialogueTools
{
    DialogueSystem::DialogueSystem()
    {
        //profile = Profile(Images + "ProfilesPlaceHolder.png", backGroundPosition + sf::Vector2f(-510, 0));
        mainWindow.setFillColor(backgroundColor);
        resetTransform();
        mainWindow.setOrigin(sf::Vector2(backGroundSize.x / 2, backGroundSize.y / 2));
        
        dialogueText.setPosition(backGroundPosition - sf::Vector2f(300, backGroundSize.y / 2 - 20));
        dialogueText.setCharacterSize(45);
    }

    DialogueSystem::~DialogueSystem() 
    {
        delete dialogueBuffer;
        delete history;
    }

    void DialogueSystem::ProcessEvent(const sf::RenderWindow& window, const sf::Event& event)
    {
        //set deltatime to unhook speeds from the framecount
        sf::Clock fpsTimer;
        sf::Text fpsCounter(font);

        if (currentDialogueName == "")
        {
            return;
        }

        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode != sf::Keyboard::Scancode::Space)
            {
                return;
            }
            else if (dialogueTexts.currentChar < dialogueTexts.rawText.getSize() -1)
            {
                dialogueTexts.currentChar = dialogueTexts.rawText.getSize();
                return;
            }
            NextDialogue();
        }
    }

    int currentemotion = 0;
    void DialogueSystem::Draw(sf::RenderWindow& window)
    {
        mainWindow.setPosition(backGroundPosition);
        mainWindow.setSize(backGroundSize);
        window.draw(mainWindow);

        profile.Draw(window);

        dialogueTexts.Draw(window);
        if (currentemotion != dialogueTexts.emotionLocs.size() && dialogueTexts.currentChar == dialogueTexts.emotionLocs[currentemotion])
        { 
            profile.SetEmotion(dialogueTexts.emotions[currentemotion]);
            currentemotion++;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Tab))
        {
            history->Draw(window);
        }
        else 
        {
            history->ButtonPrompt(window);
        }
    }

    void DialogueSystem::InitDialogue(std::string dialogueName)
    {
        currentDialogueName = dialogueName;

        *dialogueBuffer = ImportText("Game/" + dialogueName + ".txt");

        StartDialogue(0);
    }

    void DialogueSystem::StartDialogue(int index)
    {
        if (index >= dialogueBuffer->size())
        {
            currentDialogueName = "";
            return;
        }

        dialogueText.setString((*dialogueBuffer)[index]);

        dialogueTexts.ProcessText(dialogueText);
        history->items.emplace_back(sf::Text(font, dialogueTexts.rawText, 45));
        currentDialogue = index;
    }

    void DialogueSystem::NextDialogue()
    {
        StartDialogue(currentDialogue + 1);
    }

    const void DialogueSystem::resetTransform()
    {
        backGroundPosition = defaultPosition;
        backGroundSize = defaultSize;
    }
}