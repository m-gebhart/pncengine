#ifndef ESPRITE_H
#define ESPRITE_H

#include "Entity.h"
#include "EAudio.h"
#include "EText.h"

class ESprite : public Entity {
public:
	sf::Sprite* pSprite;
	sf::Texture* pTexture;
	rapidxml::xml_node<>* pNodeInAssets;
	rapidxml::xml_node<>* pNodeInScene;
	EAudio* pAudio;
	EText* pText;
	bool onClickAudio = false;
	bool onClickText = false;

	ESprite();
	ESprite(rapidxml::xml_node<>* spriteNode);
	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetPosition();
	void MoveTo(sf::Vector2f movement, int speed);
	void SetScale(sf::Vector2f rot);
	void SetRotation(float rotation);
	void SetOrigin(sf::Vector2f origin);

	void UpdateSpriteData(rapidxml::xml_node<>* spriteSceneNode);
	void SetUpAudio(const char* audioData);
	void SetUpText(const char* textData);
	bool ClickedOn(sf::Vector2f clickPos);
};
#endif