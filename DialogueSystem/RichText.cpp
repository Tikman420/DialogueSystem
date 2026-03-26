#include "RichText.h"

namespace DialogueTools
{
    void RichText::ProcessText(sf::Text& dialogueBox)
    {
        sf::String text = dialogueBox.getString();

        words.clear();
        Texts.clear();
        Texts.emplace_back(dialogueBox);

        WordWrapping(text, WrappingCount);
        rawText = Effects(words);
        dialogueBox.setString(text);

        //reset typewriter
        currentChar = 0;
        typewriterTimer = 0;
    }

    void RichText::Draw(sf::RenderWindow& window) 
    {
        int length = 0;
        //window.draw(TypeWriter(dialogueText));
        for (auto i = Texts.begin(); i != Texts.end(); i++)
        {
            window.draw(TypeWriter(*i, length));
            length += i->getString().getSize();
        }
    }

    void RichText::WordWrapping(sf::String& text, int wrapLength)
    {
        int lastSpace = 0;
        int lastEnter = 0;
        int currentText = 0;
        for (int i = 0; i < text.getSize(); i++)
        {
            if (text[i] == ' ' || text[i] == '\n')
            {
                words.emplace_back(text.substring(lastSpace, i-lastSpace));
                if (words.back()[0] == ' ')
                {
                    words.back() = words.back().substr(1);
                }

                lastSpace = i;
                continue;
            }

            if (i - lastSpace > wrapLength)
            {
                sf::String original = Texts[currentText].getString();
                original.insert(i - 3, "-");
                Texts[currentText].setString(original);
                SplitText(currentText, i - lastEnter, 0);
                currentText++;
                Wrap(currentText);
                lastSpace = lastEnter = i;
                continue;
            }

            if (i - lastEnter > wrapLength)
            {
                text[lastSpace] = '\n';
                SplitText(currentText, lastSpace - lastEnter,0);
                currentText++;
                Wrap(currentText);
                lastEnter = lastSpace;
            }
        }
        words.emplace_back(text.substring(lastSpace+1));
    }

    void RichText::Wrap(int wrappedTextIndex)
    {
        float spacing = Texts[wrappedTextIndex].getLineSpacing() + Texts[wrappedTextIndex].getCharacterSize();
        Texts[wrappedTextIndex].setPosition(Texts[wrappedTextIndex - 1].getPosition() + sf::Vector2f(0, spacing));
    }

    void RichText::SplitText(int originalTextIndex, int cutoff, int removeableLength)
    {
        std::string original = Texts[originalTextIndex].getString();
        sf::Text newText = sf::Text(Texts[originalTextIndex]);
        std::string newLine = original.substr(cutoff);
        if (newLine[0] == ' ')
        {
            newLine = newLine.substr(1);
        }

        newText.setString(newLine);
        newText.setPosition(Texts[originalTextIndex].findCharacterPos(cutoff-removeableLength+1));

        Texts[originalTextIndex].setString(original.substr(0, cutoff-removeableLength));
        Texts.insert(Texts.begin() + originalTextIndex + 1, newText);
    }

    sf::String RichText::Effects(std::vector<std::string> seperatedWords)
    {
        sf::String removed;
        int length = 0;
        int currentText = 0;

        for (int i = 0; i != seperatedWords.size(); i++)
        {
            if (seperatedWords[i][0] == '\n')
            {
                seperatedWords[i] = seperatedWords[i].substr(1);
                length = 0;
                currentText++;
            }
            length += seperatedWords[i].size() + 1;
            if (seperatedWords[i] == "<!>")
            {
                SplitText(currentText, length, 4);
                currentText++;
                Texts[currentText].setFillColor(importantColor);
                Texts[currentText].setStyle(sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined);

                length = 0;
                continue;
            }
            if (seperatedWords[i].find("</") != -1)
            {
                SplitText(currentText, length, seperatedWords[i].size()+1);
                currentText++;
                Texts[currentText].setFillColor(Texts[0].getFillColor());
                Texts[currentText].setStyle(sf::Text::Regular);
                Texts[currentText].setCharacterSize(Texts[0].getCharacterSize());
                length = 0;
                continue;
            }
            if (seperatedWords[i] == "<w>")
            {
                SplitText(currentText, length, 4);
                currentText++;
                Texts[currentText].setFillColor(whisperColor);
                Texts[currentText].setStyle(sf::Text::Italic);
                Texts[currentText].setCharacterSize(whisperSize);
                length = 0;
                continue;
            }
            removed += seperatedWords[i] + " ";
        }
        return removed;
    }

    sf::Text RichText::TypeWriter(sf::Text writer, int offset)
    {
        std::string text = writer.getString();
        if (currentChar - offset < 0 || currentChar - offset >= text.size())
        {
            goto setString;
        }
        if (currentChar - offset != text.size() && typewriterTimer <= 0)
        {
            char character = text[currentChar - offset];
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
        if (currentChar - offset >= text.size() && currentChar - offset > 0)
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
}