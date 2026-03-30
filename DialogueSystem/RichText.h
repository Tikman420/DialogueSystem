#pragma once
#include "Include.h"

namespace DialogueTools 
{
    class RichText
    {
    private:
        const sf::Color importantColor = sf::Color(255,0,0,255);
        const sf::Color whisperColor = sf::Color(100,100,100,255);
        const float whisperSize = 33;

        //TypeWriter settings
        const float normalDelay = 0.05;
        const float punctuationDelay = 0.1;

        int WrappingCount = 40; //in pixels

        float typewriterTimer = 0;

        //text handling
        void WordWrapping(sf::String& text, int wrapLength);
        void Wrap(int wrappedTextIndex);
        void SplitText(int originalTextIndex, int cutoff, int removeableLength);
        sf::String Effects(std::vector<std::string> seperatedWords);
        std::vector<std::string> words = std::vector<std::string>();

    public:
        std::vector<sf::Text> Texts = std::vector<sf::Text>();
        sf::String rawText;
        std::vector<int> emotionLocs = std::vector<int>();
        std::vector<std::string> emotions = std::vector<std::string>();

        int currentChar = 0;

        void Draw(sf::RenderWindow& window);
        void ProcessText(sf::Text& dialogueBox);
        sf::Text TypeWriter(sf::Text writer, int offset);
    };
}

