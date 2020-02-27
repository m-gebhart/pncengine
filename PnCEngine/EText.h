#ifndef ETEXT_H
#define ETEXT_H

#include "Entity.h"

class EText : public Entity {
	sf::Font font;
	int size;
	std::string style;
	std::string color;

public:
	std::string content;
	sf::Text text;
	rapidxml::xml_node<>* pNodeInAssets;
	float displayTime = 2;
	bool displayed;

	EText();
	EText(rapidxml::xml_node<>* textNode);
	void SetPosition(sf::Vector2f newPos);
	void SetContent(std::string newText);
	void ApplyDefaultTextData(rapidxml::xml_node<>* textNode);
	void UpdateTextData(rapidxml::xml_node<>* textSceneNode);
};
#endif