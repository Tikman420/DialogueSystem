#include "DialogueSystem.h"

extern float deltaTime;

sf::Font font = sf::Font("Game/Fonts/Roboto-Regular.ttf");
std::string Images = "Game/Images/";

namespace DialogueTools
{
    //setup dialogue window
    DialogueSystem::DialogueSystem()
    {
        mainWindow.setFillColor(backgroundColor);
        resetTransform();
        mainWindow.setOrigin(sf::Vector2(Size.x / 2, Size.y / 2));
        nameWindow.setFillColor(backgroundColor);
        name.setPosition(namePosition + padding);
        
        dialogueText.setPosition(Position - sf::Vector2f(300, Size.y / 2 - 20));
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

    //draw text window
    int emotionIndex = 0;
    void DialogueSystem::Draw(sf::RenderWindow& window)
    {
        window.draw(mainWindow);

        dialogueTexts.Draw(window);
        if (emotionIndex != dialogueTexts.emotionLocs.size() && dialogueTexts.currentChar >= dialogueTexts.emotionLocs[emotionIndex])
        { 
            currentEmotion = dialogueTexts.emotions[emotionIndex];
            profiles[dialogueTexts.currentSpeaker].SetEmotion(currentEmotion);
            emotionIndex++;
        }

        if (dialogueTexts.currentChar != currentChar && dialogueTexts.currentChar % characterPerTalk == 0) 
        {
            profiles[dialogueTexts.currentSpeaker].SetEmotion(currentEmotion + ((profiles[dialogueTexts.currentSpeaker].currentEmotion == currentEmotion) ? "talk" : ""));
            currentChar = dialogueTexts.currentChar;
        }
        //do blinking
        if (blinkTimer >= blink)
        {
            profiles[dialogueTexts.currentSpeaker].SetEmotion(currentEmotion + "blink");

            if (blinkStayTimer >= blinkLength)
            {
                profiles[dialogueTexts.currentSpeaker].SetEmotion(currentEmotion);
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

        profiles[dialogueTexts.currentSpeaker].Draw(window);

        window.draw(nameWindow);
        window.draw(name);

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
        name.setString(profiles[dialogueTexts.currentSpeaker].profileName);
        currentDialogue = index;
        emotionIndex = 0;
    }

    //advance to the next dialogue
    void DialogueSystem::NextDialogue()
    {
        StartDialogue(currentDialogue + 1);
    }

    //reset the transform of the dialogue window to the default values
    const void DialogueSystem::resetTransform()
    {
        mainWindow.setPosition(Position);
        mainWindow.setSize(Size);

        nameWindow.setPosition(namePosition);
        nameWindow.setSize(nameSize);
    }
}