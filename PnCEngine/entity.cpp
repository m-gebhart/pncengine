#include "Entity.h"
#include "Editor.h"

void Entity::SetPosition(sf::Vector2i newPos) {
	pos = newPos;
	if (pSprite != NULL)
		pSprite->setPosition(newPos.x, newPos.y);
}

sf::Vector2f Entity::GetPosition() {
	return pSprite->getPosition();
}

void Entity::SetScale(sf::Vector2f newScale) {
	scale = newScale;
	if (pSprite != NULL)
		pSprite->setScale(newScale.x, newScale.y);
}

void Entity::SetOrigin(sf::Vector2f newOrigin) {
	if (pSprite != NULL)
		pSprite->setOrigin(newOrigin.x, newOrigin.y);
}

void Entity::SetRotation(float newRot) {
	rot = newRot;	
	if (pSprite != NULL)
		pSprite->setRotation(newRot);
}

void Entity::ApplyDefaultAssetData(rapidxml::xml_node<>* spriteNode) {
	//applying default values from node in assets
	if (Editor::GetAttribute(spriteNode, "position") == NULL) {
		pos.x = 0;
		pos.y = pos.x;
	}
	else
		pos = Editor::GetAttributeVector2iValue(spriteNode, "position");

	if (Editor::GetAttribute(spriteNode, "scale") == NULL) {
		scale.x = 1;
		scale.y = scale.x;
	}
	else
		scale = Editor::GetAttributeVector2fValue(spriteNode, "scale");

	if (Editor::GetAttribute(spriteNode, "origin") == NULL) {
		ori.x = 1;
		ori.y = ori.x;
	}
	else
		ori = Editor::GetAttributeVector2fValue(spriteNode, "origin");

	if (Editor::GetAttribute(spriteNode, "rotation") == NULL)
		rot = 0;
	else
		rot = atoi(Editor::GetAttributeValue(spriteNode, "rotation"));

	if (Editor::GetAttribute(spriteNode, "id") != NULL)
		assetId = Editor::GetAttributeValue(spriteNode, "id");
	
	if (Editor::GetAttribute(spriteNode, "src") != NULL)
		src = Editor::assetPath + Editor::GetAttributeValue(spriteNode, "src");
}

void Entity::UpdateAssetData(rapidxml::xml_node<>* sceneAssetNode) {
	if (Editor::GetAttribute(sceneAssetNode, "position") != NULL) {
		pos = Editor::GetAttributeVector2iValue(sceneAssetNode, "position");
		SetPosition(pos);
	}

	if (Editor::GetAttribute(sceneAssetNode, "scale") != NULL) {
		scale = Editor::GetAttributeVector2fValue(sceneAssetNode, "scale");
		SetScale(scale);
	}

	if (Editor::GetAttribute(sceneAssetNode, "rotation") != NULL) {
		rot = atoi(Editor::GetAttributeValue(sceneAssetNode, "rotation"));
		SetRotation(rot);
	}

	if (Editor::GetAttribute(sceneAssetNode, "origin") != NULL) {
		ori = Editor::GetAttributeVector2fValue(sceneAssetNode, "origin");
		SetOrigin(ori);
	}
}