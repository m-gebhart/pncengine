#ifndef ENTITY_H
#define ENTITY_H

#include "XML_Base.h"

struct Entity {
	const char* assetId;
	std::string src;
	bool instantiated = false;

	sf::Vector2i pos;
	sf::Vector2f scale;
	sf::Vector2f ori;
	float rot;

	void ApplyDefaultAssetData(rapidxml::xml_node<>* dataNode);
};
#endif