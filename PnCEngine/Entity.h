#ifndef ENTITY_H
#define ENTITY_H

#include "XML_Base.h"

struct Entity
{
	const char* assetId;
	std::string src;

	sf::Vector2i pos;
	sf::Vector2f scale;
	sf::Vector2f ori;
	float rot;

	//---for ESprite and Esprite in EPlayer
	sf::Sprite* pSprite;
	sf::Texture* pTexture;

	void ApplyDefaultAssetData(rapidxml::xml_node<>* dataNode);
	void UpdateAssetData(rapidxml::xml_node<>* dataNode);
	void SetPosition(sf::Vector2i pos);
	sf::Vector2f GetPosition();
	void MoveTo(sf::Vector2f movement, int speed);
	void SetScale(sf::Vector2f rot);
	void SetRotation(float rotation);
	void SetOrigin(sf::Vector2f origin);
};
#endif