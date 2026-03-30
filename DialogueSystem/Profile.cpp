#include "Profile.h"



void DialogueTools::Profile::SetEmotion(std::string emotionName)
{
	std::transform(emotionName.begin(), emotionName.end(), emotionName.begin(), 
		[](unsigned char c) { return std::tolower(c); });
	currentemotionIndex = (*profileDictionary)[emotionName];
	currentEmotion = emotionName;
}

void DialogueTools::Profile::LoadJson(std::filesystem::path JsonLocation)
{
	std::vector<std::string> items = ImportText(JsonLocation);
	int start = 0;

	for (auto i = items.begin(); i != items.end(); i++) 
	{
		if (i->find("\"") == -1)
		{
			continue;
		}
		start = i->find("\"")+1;
		std::string variable = i->substr(start, i->rfind("\"", i->find(":")) - start);

		if (variable == "name") 
		{
			start = i->find("\"", i->find(":")) + 1;
			std::string amount = i->substr(start, i->rfind("\"") - start);

			profileName = amount;
		}
		else if (variable == "size") 
		{
			sf::Vector2i amount;
			start = i->find("[ ", i->find(":")) + 1;
			int middle = i->rfind(",") - start;
			amount.x = std::atoi(i->substr(start, middle).c_str());
			amount.y = std::atoi(i->substr(middle, i->rfind(" ]") - middle).c_str());

			spriteSize = amount;
		}

		if (i->back() != '[')
		{
			continue;
		}

		i++;
		int emotionIndex = 0;
		while (i->back() != ']')
		{
			start = i->find("\"") + 1;
			std::string emotion = i->substr(start, i->rfind("\"") - start);
			profileDictionary->emplace(emotion, emotionIndex);
			profileDictionary->emplace(emotion + "talk", emotionIndex + 1);
			profileDictionary->emplace(emotion + "blink", emotionIndex + 2);
			emotionIndex += 3;
			i++;
		}
	}
}

void DialogueTools::Profile::Draw(sf::RenderWindow& window) 
{
	window.draw((*emotions)[currentemotionIndex]);
}

DialogueTools::Profile::Profile(std::filesystem::path profileLocation, sf::Vector2f position)
{
	texture.loadFromFile(profileLocation);
	LoadJson(profileLocation.replace_extension(".Json"));

	for (int i = 0; i != profileDictionary->size(); i++) 
	{
		emotions->emplace_back(sf::Sprite(texture, sf::IntRect(sf::Vector2i(spriteSize.x*i, 0), spriteSize)));
		(*emotions)[i].setOrigin(sf::Vector2f((*emotions)[i].getTextureRect().size.x / 2, (*emotions)[i].getTextureRect().size.y / 2));
		(*emotions)[i].setScale(sf::Vector2f(1.5, 1.5));
		(*emotions)[i].setPosition(position);
	//sprite.setPosition(position);
	}
}

//DialogueTools::Profile::Profile(Profile& other)
//{
//	delete profileDictionary;
//	profileDictionary = other.profileDictionary;
//
//	delete emotions;
//	emotions = other.emotions;
//}
//
//DialogueTools::Profile::~Profile()
//{
//	delete profileDictionary;
//	delete emotions;
//}
