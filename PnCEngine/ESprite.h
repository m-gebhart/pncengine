#pragma once
#include "EEntity.h"

class ESprite : public EEntity {
public:
	const char* assetId;
	std::string src;
	sf::Sprite* pSprite;
	sf::Texture* pTexture;

	ESprite();
	ESprite(rapidxml::xml_node<>* spriteNode);
};