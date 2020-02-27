#ifndef ESPRITE_H
#define ESPRITE_H

#include "Entity.h"
#include "EAudio.h"

class ESprite : public Entity {
public:
	sf::Sprite* pSprite;
	sf::Texture* pTexture;
	rapidxml::xml_node<>* pNodeInAssets;
	rapidxml::xml_node<>* pNodeInScene;
	EAudio* pAudio;
	bool onClickAction = false;

	ESprite();
	ESprite(rapidxml::xml_node<>* spriteNode);
	void SetPosition(sf::Vector2i pos);
	sf::Vector2f GetPosition();
	void MoveTo(sf::Vector2f movement, int speed);
	void SetScale(sf::Vector2f rot);
	void SetRotation(float rotation);
	void SetOrigin(sf::Vector2f origin);

	void UpdateSpriteData(rapidxml::xml_node<>* spriteNode);
	void SetUpAudio(const char* audioData);
	bool ClickedOn(sf::Vector2f clickPos);
};
#endif