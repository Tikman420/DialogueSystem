#include "RichText.h"

namespace DialogueTools
{
    //preprocess the text
    void RichText::ProcessText(sf::Text& dialogueBox)
    {
        sf::String text = dialogueBox.getString();

        //reset vectors
        words.clear();
        Texts.clear();
        //set first text
        Texts.emplace_back(dialogueBox);

        //put effects on the text
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
        //draw each text
        for (auto i = Texts.begin(); i != Texts.end(); i++)
        {
            window.draw(TypeWriter(*i, length));
            length += i->getString().getSize();
        }
    }

    //wrap words
    void RichText::WordWrapping(const sf::String& text, int wrapLength)
    {
        int lastSpace = 0;
        int lastEnter = 0;
        int currentText = 0;
        for (int i = 0; i < text.getSize(); i++)
        {
            //split the words for later
            if (text[i] == ' ' || text[i] == '\n')
            {
                words.emplace_back(text.substring(lastSpace, i-lastSpace));
                if (words.back()[0] == ' ')
                {
                    words.back() = words.back().substr(1);
                }
                if (lastEnter == lastSpace && lastEnter != 0) 
                {
                    words.back().insert(0, "\n");
                }

                lastSpace = i;
                continue;
            }

            //if the word is longer than wraplength
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

            //if the amount of characters is more than wraplength
            if (i - lastEnter > wrapLength)
            {
                SplitText(currentText, lastSpace - lastEnter,0);
                currentText++;
                Wrap(currentText);
                lastEnter = lastSpace;
            }
        }
        //add last word to the word list
        words.emplace_back(text.substring(lastSpace+1));
    }

    void RichText::Wrap(const int& wrappedTextIndex)
    {
        float spacing = Texts[wrappedTextIndex].getLineSpacing() + Texts[wrappedTextIndex].getCharacterSize();
        Texts[wrappedTextIndex].setPosition(Texts[wrappedTextIndex - 1].getPosition() + sf::Vector2f(0, spacing));
    }

    void RichText::SplitText(const int& originalTextIndex, const int& cutoff, const int& removeableLength)
    {
        std::string original = Texts[originalTextIndex].getString();
        sf::Text newText = sf::Text(Texts[originalTextIndex]);
        std::string newLine = original.substr(cutoff);

        //remove space if it's in the text
        if (newLine[0] == ' ')
        {
            newLine = newLine.substr(1);
        }

        //set the new text
        newText.setString(newLine);
        newText.setPosition(Texts[originalTextIndex].findCharacterPos(cutoff-removeableLength+1));

        //cut the original text back before removableLength
        Texts[originalTextIndex].setString(original.substr(0, cutoff-removeableLength));
        Texts.insert(Texts.begin() + originalTextIndex + 1, newText);
    }

    const sf::String RichText::Effects(std::vector<std::string> seperatedWords)
    {
        //reset emotions
        emotionLocs.clear();
        emotions.clear();
        sf::String removed;
        int length = 0;
        int currentText = 0;

        //check per word if its one of the following effects
        for (int i = 0; i != seperatedWords.size(); i++)
        {
            //apply changes to the next text
            if (seperatedWords[i][0] == '\n')
            {
                seperatedWords[i] = seperatedWords[i].substr(1);
                length = 0;
                currentText++;
            }
            length += seperatedWords[i].size() + 1;
            //make important
            if (seperatedWords[i] == "<!>")
            {
                SplitText(currentText, length, 4);
                currentText++;
                Texts[currentText].setFillColor(importantColor);
                Texts[currentText].setStyle(sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined);

                length = 0;
                continue;
            }
            //undo effects
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
            //wisper effect
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
            //change emotion
            if (seperatedWords[i].find("<e:") != -1) 
            {
                if (removed.getSize() == 0) 
                {
                    Texts[currentText].setString(Texts[currentText].getString().substring(seperatedWords[i].size() + 1));
                    length -= seperatedWords[i].size();
                }
                else 
                {
                    SplitText(currentText, length, seperatedWords[i].size() + 2);
                    currentText++;
                    length = 0;
                }

                emotionLocs.emplace_back(removed.getSize());
                emotions.emplace_back(seperatedWords[i].substr(3, seperatedWords[i].size()-4));
                continue;
            }
            //change Character
            if (seperatedWords[i].find("<c:") != -1) 
            {
                currentSpeaker = atoi(seperatedWords[i].substr(3, seperatedWords[i].size()-3).c_str());
                Texts[currentText].setString(std::string(Texts[currentText].getString()).erase(removed.getSize(), seperatedWords[i].size()+1));
                length -= seperatedWords[i].size();
                continue;
            }
            removed += seperatedWords[i] + " ";
        }
        return removed;
    }

    const sf::Text RichText::TypeWriter(sf::Text writer, int offset)
    {
        std::string text = writer.getString();
        //only do writing when it is this texts turn
        if (currentChar - offset >= 0 && currentChar - offset < text.size())
        {
            if (currentChar - offset != text.size() && typewriterTimer <= 0)
            {
                char character = text[currentChar - offset];
                if (punctuation.find(character) != punctuation.end())
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
        }

        //apply the amount erased
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