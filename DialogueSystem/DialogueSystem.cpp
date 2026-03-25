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

        int length = 0;
        //window.draw(TypeWriter(dialogueText));
        for (auto i = dialogueTexts.begin(); i != dialogueTexts.end(); i++) 
        {
            window.draw(TypeWriter(*i, length));
            length += i->getString().getSize();
        }
    }

    void DialogueSystem::ProcessText(sf::Text& dialogueBox)
    {
        sf::String text = dialogueBox.getString();
        WordWrapping(text, WrappingCount);
        dialogueBox.setString(text);
    }

    void DialogueSystem::WordWrapping(sf::String& text, int wrapLength)
    {
        int lastSpace = 0;
        int lastEnter = 0;
        int currentText = 0;
        for (int i = 0; i < text.getSize(); i++)
        {
            if (text[i] == ' ' || text[i] == '\n')
            {
                lastSpace = i;
                continue;
            }

            if (i - lastSpace > wrapLength)
            {
                sf::String original = dialogueTexts[currentText].getString();
                original.insert(i-3, "-");
                dialogueTexts[currentText].setString(original);
                SplitText(currentText, i - lastEnter);
                currentText++;
                Wrap(currentText);
                lastSpace = lastEnter = i;
                continue;
            }

            if (i - lastEnter > wrapLength)
            {
                text[lastSpace] = '\n';
                SplitText(currentText, lastSpace - lastEnter);
                currentText++;
                Wrap(currentText);
                lastEnter = lastSpace;
            }
        }
    }

    void DialogueSystem::Wrap(int wrappedTextIndex) 
    {
        float spacing = dialogueTexts[wrappedTextIndex].getLineSpacing() + dialogueTexts[wrappedTextIndex].getCharacterSize();
        dialogueTexts[wrappedTextIndex].setPosition(dialogueTexts[wrappedTextIndex-1].getPosition() + sf::Vector2f(0, spacing));
    }

    void DialogueSystem::SplitText(int originalTextIndex, int cutoff) 
    {
        std::string original = dialogueTexts[originalTextIndex].getString();
        sf::Text newText = sf::Text(dialogueTexts[originalTextIndex]);
        std::string newLine = original.substr(cutoff);
        if (newLine[0] == ' ')
        {
            newLine = newLine.substr(1);
        }

        newText.setString(newLine);
        newText.setPosition(dialogueTexts[originalTextIndex].findCharacterPos(cutoff));

        dialogueTexts[originalTextIndex].setString(original.substr(0,cutoff));
        dialogueTexts.insert(dialogueTexts.begin() + originalTextIndex + 1, newText);
    }

    sf::Text DialogueSystem::TypeWriter(sf::Text writer, int offset)
    {
        std::string text = writer.getString();
        if (currentChar - offset < 0 || currentChar - offset >= text.size())
        {
            std::cout << ((currentChar - offset < 0) ? "true" : "false") + std::to_string(currentChar) + std::string(" smaller: ") + ((currentChar - offset > text.size()) ? "true" : "false") << std::endl;
            goto setString;
        }
        if (currentChar - offset != text.size() && typewriterTimer <= 0)
        {
            char character = text[currentChar-offset];
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
        else if (currentChar - offset != text.size())
        {
            typewriterTimer -= Tools::GetDeltaTime();
        }

    setString:
        if (currentChar-offset >= text.size() && currentChar - offset > 0)
        {
            return writer;
        }
        if (currentChar - offset > 0)
        {
            text.erase(currentChar - offset);
        }
        else
        {
            text.erase(0);
        }
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

        dialogueText.setString((*dialogueBuffer)[index]);

        dialogueTexts.clear();
        dialogueTexts.emplace_back(dialogueText);

        ProcessText(dialogueText);
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