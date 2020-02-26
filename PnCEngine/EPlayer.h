#ifndef EPLAYER_H
#define EPLAYER_H

#include "Entity.h"
#include "ESprite.h"
#include "EScene.h"

class EPlayer {
	int movementSpeed;
	sf::Vector2f currentMovement;
public:
	sf::Vector2f targetPos;
	ESprite* pPlayerSprite;
	bool moving = false;
	int moveLimit[4];

	EPlayer();
	EPlayer(rapidxml::xml_node<>* assetNode);
	void ApplyDefaultPlayerData(rapidxml::xml_node<>* playerSceneNode);
	void UpdatePlayerData(rapidxml::xml_node<>* playerSceneNode);
	void SetTargetPosition(sf::Vector2f pos);
	bool TargetReached();
	void MoveToTargetPosition();
	sf::Vector2f GetMovementVector(sf::Vector2f targetPos);
};
#endif