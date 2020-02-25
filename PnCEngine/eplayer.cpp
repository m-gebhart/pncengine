#include "EPlayer.h"
#include "Editor.h"

EPlayer::EPlayer() {} 

EPlayer::EPlayer(rapidxml::xml_node<>* playerNode) {
	pPlayerSprite = new ESprite(playerNode);
	ApplyDefaultPlayerData(playerNode);
}

void EPlayer::SetTargetPosition(sf::Vector2i newPos) {
	targetPos = newPos;
	//pPlayerSprite->pSprite->setPosition(targetPos.x, targetPos.y);
	moving = true;
}

void EPlayer::SetTargetPosition(sf::Vector2f newPos) {
	targetPos.x = (int)newPos.x;
	targetPos.y = (int)newPos.y;
	//pPlayerSprite->pSprite->setPosition(targetPos.x, targetPos.y);
	moving = true;
}

void EPlayer::MoveToTargetPosition() {
	if (targetPos != pPlayerSprite->pos) {
		MoveTo(targetPos);
	}
	else
		moving = false;
	pPlayerSprite->pos.x = int(pPlayerSprite->pSprite->getPosition().x);
	pPlayerSprite->pos.y = int(pPlayerSprite->pSprite->getPosition().y);
}

void EPlayer::MoveTo(sf::Vector2i targetPos) {
	if (pPlayerSprite->pos.x < targetPos.x - movementSpeed.x/2)
		pPlayerSprite->pSprite->move(movementSpeed.x, 0);
	else if (pPlayerSprite->pos.x > targetPos.x + movementSpeed.x / 2)
		pPlayerSprite->pSprite->move(-movementSpeed.x, 0);
	
	if (pPlayerSprite->pos.y < targetPos.y - movementSpeed.y/2)
		pPlayerSprite->pSprite->move(0, movementSpeed.y);
	else if (pPlayerSprite->pos.y > targetPos.y + movementSpeed.y/2)
		pPlayerSprite->pSprite->move(0, -movementSpeed.y);
}

void EPlayer::ApplyDefaultPlayerData(rapidxml::xml_node<>* spriteNode) {
	//applying default values from player node in assets
	if (Editor::GetAttribute(spriteNode, "speed") == NULL) {
		movementSpeed.x = 10;
		movementSpeed.y = 5;
	}
	else
		movementSpeed = Editor::GetAttributeVector2iValue(spriteNode, "speed");
}

void EPlayer::UpdatePlayerData(rapidxml::xml_node<>* sceneAssetNode) {
	if (Editor::GetAttribute(sceneAssetNode, "speed") != NULL) {
		movementSpeed = Editor::GetAttributeVector2iValue(sceneAssetNode, "speed");
	}
}