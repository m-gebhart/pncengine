#ifndef EPLAYER_H
#define EPLAYER_H

#include "Entity.h"
#include "ESprite.h"

class EPlayer {
	sf::Vector2i movementSpeed;
public:
	sf::Vector2i targetPos;
	ESprite* pPlayerSprite;
	bool moving = false;

	EPlayer();
	EPlayer(rapidxml::xml_node<>* assetNode);
	void ApplyDefaultPlayerData(rapidxml::xml_node<>* playerSceneNode);
	void UpdatePlayerData(rapidxml::xml_node<>* playerSceneNode);
	void SetTargetPosition(sf::Vector2i pos);
	void SetTargetPosition(sf::Vector2f pos);
	void MoveToTargetPosition();
	void MoveTo(sf::Vector2i target);
};
#endif