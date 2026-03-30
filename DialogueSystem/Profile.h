#pragma once
#include "Include.h"

namespace DialogueTools
{
	class Profile
	{
	private:
		std::map<std::string, int>* profileDictionary = new std::map<std::string, int>();
		std::vector<sf::Sprite>* emotions = new std::vector<sf::Sprite>();
		sf::Texture texture;
		sf::Vector2i spriteSize;
	public:
		int currentemotion;
		std::string profileName;

		void SetEmotion(std::string emotionName);
		void LoadJson(std::filesystem::path JsonLocation);
		void Draw(sf::RenderWindow& window);
		Profile(std::filesystem::path profileLocation, sf::Vector2f position);
		Profile() = default;
		/*Profile(Profile& other);
		~Profile();*/
	};
}