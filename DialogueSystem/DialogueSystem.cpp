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
            if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
            {
                NextDialogue();
            }
        }
    }

    void DialogueSystem::Draw(sf::RenderWindow& window)
    {
        mainWindow.setPosition(backGroundPosition);
        mainWindow.setSize(backGroundSize);
        window.draw(mainWindow);

        profile.setPosition(backGroundPosition + sf::Vector2f(-510, 0));
        window.draw(profile);

        window.draw(TypeWriter(dialogueText));
    }

    void DialogueSystem::RenderText(sf::Text& dialogueBox, std::string text)
    {
        WordWrapping(text, WrappingCount);
        dialogueBox.setString(text);
    }

    void DialogueSystem::WordWrapping(std::string& text, int wrapLength)
    {
        int lastSpace = 0;
        int lastEnter = 0;
        for (int i = 0; i < text.size(); i++)
        {
            if (text[i] == ' ' || text[i] == '\n')
            {
                lastSpace = i;
            }

            if (i - lastSpace > wrapLength)
            {
                text.insert(i, "-\n");
                lastSpace = lastEnter = i;
                continue;
            }

            if (i - lastEnter > wrapLength)
            {
                text[lastSpace] = '\n';
                lastEnter = lastSpace;
            }
        }
    }

    sf::Text DialogueTools::DialogueSystem::TypeWriter(sf::Text writer)
    {
        std::string text = writer.getString();
        if (currentChar != text.size() && typewriterTimer <= 0)
        {

            char character = text[currentChar];
            if (character == '.' || character == '?' || character == '!' || character == '*' || 
                character == ',' || character == '/' || character == '\\' || character == ';' || 
                character == ':' || character == '-')
            {
                typewriterTimer = punctuationDelay;
            }
            else 
            {
                typewriterTimer = normalDelay;
            }

            currentChar++;
        }
        else if (currentChar != text.size())
        {
            typewriterTimer -= Tools::GetDeltaTime();
        }

        text.erase(currentChar, text.size() - currentChar);
        writer.setString(text);
        return writer;
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

        RenderText(dialogueText, (*dialogueBuffer)[index]);
        currentDialogue = index;
        currentChar = 0;
        typewriterTimer = 0;
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