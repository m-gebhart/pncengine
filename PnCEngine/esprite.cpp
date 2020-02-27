#include "ESprite.h"
#include "Editor.h"

ESprite::ESprite() {}

ESprite::ESprite(rapidxml::xml_node<>* spriteNode) {	
	pNodeInAssets = spriteNode;
	ApplyDefaultAssetData(spriteNode);

	pSprite = new sf::Sprite();
	pTexture = new sf::Texture();
	pTexture->loadFromFile(src);
	pSprite->setTexture(*pTexture);
	ESprite::SetPosition(pos);
	ESprite::SetScale(scale);
	ESprite::SetOrigin(ori);
	ESprite::SetRotation(rot);
}

void ESprite::SetPosition(sf::Vector2i newPos) {
	pos = newPos;
	if (pSprite != NULL)
		pSprite->setPosition(newPos.x, newPos.y);
}

sf::Vector2f ESprite::GetPosition() {
	return pSprite->getPosition();
}

void ESprite::SetScale(sf::Vector2f newScale) {
	scale = newScale;
	if (pSprite != NULL)
		pSprite->setScale(newScale.x, newScale.y);
}

void ESprite::SetOrigin(sf::Vector2f newOrigin) {
	if (pSprite != NULL)
		pSprite->setOrigin(newOrigin.x, newOrigin.y);
}

void ESprite::SetRotation(float newRot) {
	rot = newRot;
	if (pSprite != NULL)
		pSprite->setRotation(newRot);
}

void ESprite::MoveTo(sf::Vector2f direction, int speed) {
	for (int lap = speed; lap > 0; lap--) {
		pSprite->move(direction);
	}
}

bool ESprite::ClickedOn(sf::Vector2f clickPos) {
	if (pSprite->getGlobalBounds().contains(clickPos))
		return true;
	return false;
}

void ESprite::UpdateSpriteData(rapidxml::xml_node<>* spriteNode) {
	pNodeInScene = spriteNode;

	if (Editor::GetAttribute(spriteNode, "position") != NULL) {
		pos = Editor::GetAttributeVector2iValue(spriteNode, "position");
		SetPosition(pos);
	}

	if (Editor::GetAttribute(spriteNode, "scale") != NULL) {
		scale = Editor::GetAttributeVector2fValue(spriteNode, "scale");
		SetScale(scale);
	}

	if (Editor::GetAttribute(spriteNode, "rotation") != NULL) {
		rot = atoi(Editor::GetAttributeValue(spriteNode, "rotation"));
		SetRotation(rot);
	}

	if (Editor::GetAttribute(spriteNode, "origin") != NULL) {
		ori = Editor::GetAttributeVector2fValue(spriteNode, "origin");
		SetOrigin(ori);
	}

	if (Editor::GetAttribute(spriteNode, "onClickAudio") != NULL)
		SetUpAudio(Editor::GetAttributeValue(spriteNode, "onClickAudio"));
}

void ESprite::SetUpAudio(const char* audioId) {
	onClickAction = true;
	for (auto &audio : Editor::audioAssets) {
		if (strcmp(audio->assetId, audioId) == 0) {
			if (audio->instantiated > 0) {
				//if sound already exists in scene, create one more instance for current ESprite
				EAudio* newAudio = new EAudio(audio->pNodeInAssets);
				newAudio->UpdateAudioData(pNodeInScene);
				newAudio->LoadSound();
				pAudio = newAudio;
			}
			else {
				audio->instantiated = true;
				audio->UpdateAudioData(pNodeInScene);
				audio->LoadSound();
				pAudio = audio;
			}
		}
	}
}