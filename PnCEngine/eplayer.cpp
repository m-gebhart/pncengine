#include "EPlayer.h"
#include "Editor.h"

EPlayer::EPlayer() {} 

EPlayer::EPlayer(rapidxml::xml_node<>* playerNode) {
	pPlayerSprite = new ESprite(playerNode);
	ApplyDefaultPlayerData(playerNode);
}

void EPlayer::ApplyDefaultPlayerData(rapidxml::xml_node<>* spriteNode) {
	//applying default values from player node in assets
	if (Editor::GetAttribute(spriteNode, "speed") == NULL)
		movementSpeed = 10;
	else
		movementSpeed = atoi(Editor::GetAttributeValue(spriteNode, "speed"));

	//insert animationSystem HERE
}

void EPlayer::UpdatePlayerData(rapidxml::xml_node<>* sceneAssetNode) {
	pPlayerSprite->UpdateAssetData(sceneAssetNode);
	if (Editor::GetAttribute(sceneAssetNode, "speed") != NULL)
		movementSpeed = atoi(Editor::GetAttributeValue(sceneAssetNode, "speed"));
}

void EPlayer::SetTargetPosition(sf::Vector2f newPos) {
	//checking for borders of movable area
	if (newPos.x < moveLimit[0])
		targetPos.x = float(moveLimit[0]);
	else if (moveLimit[2] < newPos.x)
		targetPos.x = float(moveLimit[2]);
	else
		targetPos.x = (int)newPos.x;

	if (newPos.y < moveLimit[1])
		targetPos.y = float(moveLimit[1]);
	else if (moveLimit[3] < newPos.y)
		targetPos.y = float(moveLimit[3]);
	else
		targetPos.y = (int)newPos.y;

	currentMovement = GetMovementVector(targetPos);
	moving = true;
}

void EPlayer::MoveToTargetPosition() {
	if (!TargetReached()) {
		pPlayerSprite->MoveTo(currentMovement, movementSpeed);
	}
	else
		moving = false;
	pPlayerSprite->pos.x = int(pPlayerSprite->pSprite->getPosition().x);
	pPlayerSprite->pos.y = int(pPlayerSprite->pSprite->getPosition().y);
}

bool EPlayer::TargetReached() {
	if (targetPos.x < pPlayerSprite->pos.x - movementSpeed/2 ||
		targetPos.x > pPlayerSprite->pos.x + movementSpeed/2 || 
		targetPos.y < pPlayerSprite->pos.y - movementSpeed/2 ||
		targetPos.y > pPlayerSprite->pos.y + movementSpeed/2)
		return false;
	return true;
}

sf::Vector2f EPlayer::GetMovementVector(sf::Vector2f targetPos) {
	float xDistance = targetPos.x - pPlayerSprite->pos.x;
	float yDistance = targetPos.y - pPlayerSprite->pos.y;
	float pythagorean = std::sqrt(xDistance*xDistance + yDistance * yDistance);
	sf::Vector2f result(xDistance / pythagorean, yDistance / pythagorean);
	return result;
}