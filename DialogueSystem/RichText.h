#pragma once
#include "Include.h"

namespace DialogueTools 
{
    class RichText
    {
    private:
        //customization options
        const sf::Color importantColor = sf::Color(255,0,0,255);
        const sf::Color whisperColor = sf::Color(100,100,100,255);
        const float whisperSize = 33;

        //TypeWriter settings
        const std::set<char> punctuation{ '.', '?', '!', '*', ',', '/', '\\', ';', ':', '-' };
        const float normalDelay = 0.05;
        const float punctuationDelay = 0.1;

        int WrappingCount = 40; //in pixels

        //dont touch
        float typewriterTimer = 0;
        std::vector<std::string> words = std::vector<std::string>();

        //text handling functions
        void WordWrapping(const sf::String& text, int wrapLength);
        void Wrap(const int& wrappedTextIndex);
        void SplitText(const int& originalTextIndex, const int& cutoff, const int& removeableLength);
        const sf::String Effects(std::vector<std::string> seperatedWords);

    public:
        //vector with rendered text
        std::vector<sf::Text> Texts = std::vector<sf::Text>();

        //complete text without the <>
        sf::String rawText;

        //locations where the emotions are
        std::vector<int> emotionLocs = std::vector<int>();
        //the emotions used in current text
        std::vector<std::string> emotions = std::vector<std::string>();

        //current speaking character
        int currentSpeaker = 0;

        //the current charracter the typewriter is on
        int currentChar = 0;

        //draw the text
        void Draw(sf::RenderWindow& window);

        //function that sets the text up
        void ProcessText(sf::Text& dialogueBox);
        const sf::Text TypeWriter(sf::Text writer, int offset);
    };
}

