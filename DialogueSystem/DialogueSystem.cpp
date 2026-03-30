#include "DialogueSystem.h"

extern float deltaTime;

namespace DialogueTools
{
    //setup dialogue window
    DialogueSystem::DialogueSystem()
    {
        //profile = Profile(Images + "ProfilesPlaceHolder.png", backGroundPosition + sf::Vector2f(-510, 0));
        mainWindow.setFillColor(backgroundColor);
        resetTransform();
        mainWindow.setOrigin(sf::Vector2(backGroundSize.x / 2, backGroundSize.y / 2));
        
        dialogueText.setPosition(backGroundPosition - sf::Vector2f(300, backGroundSize.y / 2 - 20));
        dialogueText.setCharacterSize(45);
    }

    //remove dialogue window
    DialogueSystem::~DialogueSystem() 
    {
        delete dialogueBuffer;
        delete history;
    }

    //process if player wants to go further
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

    //draw window
    void DialogueSystem::Draw(sf::RenderWindow& window)
    {
        mainWindow.setPosition(backGroundPosition);
        mainWindow.setSize(backGroundSize);
        window.draw(mainWindow);

        dialogueTexts.Draw(window);
        int emotionIndex = 0;
        if (emotionIndex != dialogueTexts.emotionLocs.size() && dialogueTexts.currentChar >= dialogueTexts.emotionLocs[emotionIndex])
        { 
            currentEmotion = dialogueTexts.emotions[emotionIndex];
            profile.SetEmotion(currentEmotion);
            emotionIndex++;
        }

        if (dialogueTexts.currentChar != currentChar && dialogueTexts.currentChar % characterPerTalk == characterPerTalk-1) 
        {
            profile.SetEmotion(currentEmotion + ((profile.currentEmotion == currentEmotion) ? "talk" : ""));
            currentChar = dialogueTexts.currentChar;
        }
        //do blinking
        if (blinkTimer >= blink)
        {
            profile.SetEmotion(currentEmotion + "blink");

            if (blinkStayTimer >= blinkLength)
            {
                profile.SetEmotion(currentEmotion);
                blinkTimer = 0;
                blinkStayTimer = 0;
            }
            else 
            {
                blinkStayTimer += deltaTime;
            }
        }
        else 
        {
            blinkTimer += deltaTime;
        }

        profile.Draw(window);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Tab))
        {
            history->Draw(window);
        }
        else 
        {
            history->ButtonPrompt(window);
        }
    }

    //start a new dialogue
    void DialogueSystem::InitDialogue(std::string dialogueName)
    {
        currentDialogueName = dialogueName;

        *dialogueBuffer = ImportText("Game/" + dialogueName + ".txt");

        StartDialogue(0);
    }

    //start the text for the dialogue
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

    //advance to the next dialogue
    void DialogueSystem::NextDialogue()
    {
        StartDialogue(currentDialogue + 1);
    }

    //reset the transform of the dialogue window to the default values
    const void DialogueSystem::resetTransform()
    {
        backGroundPosition = defaultPosition;
        backGroundSize = defaultSize;
    }
}