#ifndef ESPRITE_H
#define ESPRITE_H

#include "Entity.h"
#include "EAudio.h"

class ESprite : public Entity {
public:
	EAudio* pAudio;
	bool onClickAction = false;

	ESprite();
	ESprite(rapidxml::xml_node<>* spriteNode);
	void UpdateSpriteData(rapidxml::xml_node<>* spriteNode);
	void SetUpAudio(const char* audioData);
	bool ClickedOn(sf::Vector2f clickPos);
};
#endif