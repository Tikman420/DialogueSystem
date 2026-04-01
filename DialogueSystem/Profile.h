#pragma once
#include "Include.h"

namespace DialogueTools
{
	class Profile
	{
	private:
		//emotion stuff
		std::map<std::string, int>* profileDictionary = new std::map<std::string, int>();
		std::vector<sf::Sprite>* emotions = new std::vector<sf::Sprite>();

		//complete texture of the spritesheet
		sf::Texture texture;
	public:
		//the size of each sprite
		sf::Vector2i spriteSize;
		//which emotion is it currently on
		int currentemotionIndex;
		//current emotion in text
		std::string currentEmotion;
		//name of the character
		std::string profileName;

		//load info for the spritesheet
		void LoadJson(std::filesystem::path JsonLocation);

		void SetEmotion(std::string emotionName);

		//draw sprite
		void Draw(sf::RenderWindow& window);

		//constructors/destructors
		Profile(std::filesystem::path profileLocation, sf::Vector2f position);
		Profile() = default;
		Profile(Profile& other);
		~Profile();
	};
}