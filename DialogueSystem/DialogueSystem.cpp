#include "DialogueSystem.h"

namespace DialogueTools
{
    std::vector<std::string> ImportText(std::string file)
    {
        //UwU: impwementot
        std::vector<std::string> result;
        std::ifstream source = std::ifstream(file, std::ios::ate);

        int size = source.tellg();
        source.seekg(0);

        std::string str;
        //https://stackoverflow.com/questions/13035674/how-to-read-a-file-line-by-line-or-a-whole-text-file-at-once
        while (std::getline(source, str))
        {
            std::cout << str << std::endl;
            result.emplace_back(str);
        }

        return result;
    }

    DialogueSystem::DialogueSystem()
    {
        mainWindow.setFillColor(backgroundColor);
        resetTransform();
        mainWindow.setOrigin(sf::Vector2(backGroundSize.x / 2, backGroundSize.y / 2));
        profile.setOrigin(sf::Vector2f(profile.getTextureRect().size.x / 2, profile.getTextureRect().size.y / 2));
        profile.setScale(sf::Vector2f(1.5, 1.5));
        dialogueText.setPosition(backGroundPosition - sf::Vector2f(300, backGroundSize.y / 2 - 20));
        dialogueText.setCharacterSize(45);

        //debug
        dialogueBuffer->push_back("Hello World!");
    }

    DialogueSystem::~DialogueSystem() 
    {
        delete dialogueBuffer;
        delete History;
        delete profileTexture;
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

    void DialogueSystem::Draw(sf::RenderWindow& window)
    {
        mainWindow.setPosition(backGroundPosition);
        mainWindow.setSize(backGroundSize);
        window.draw(mainWindow);

        profile.setPosition(backGroundPosition + sf::Vector2f(-510, 0));
        window.draw(profile);

        dialogueTexts.Draw(window);
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