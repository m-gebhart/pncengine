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

void ESprite::SetPosition(sf::Vector2f newPos) {
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
	ori = newOrigin;
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

void ESprite::UpdateSpriteData(rapidxml::xml_node<>* spriteSceneNode) {
	pNodeInScene = spriteSceneNode;

	if (Editor::GetAttribute(spriteSceneNode, "position") != NULL)
		SetPosition(Editor::GetAttributeVector2fValue(spriteSceneNode, "position"));

	if (Editor::GetAttribute(spriteSceneNode, "scale") != NULL)
		SetScale(Editor::GetAttributeVector2fValue(spriteSceneNode, "scale"));
	
	if (Editor::GetAttribute(spriteSceneNode, "rotation") != NULL)
		SetRotation(atoi(Editor::GetAttributeValue(spriteSceneNode, "rotation")));

	if (Editor::GetAttribute(spriteSceneNode, "origin") != NULL)
		SetOrigin(Editor::GetAttributeVector2fValue(spriteSceneNode, "origin"));

	if (Editor::GetAttribute(spriteSceneNode, "onClickAudio") != NULL)
		SetUpAudio(Editor::GetAttributeValue(spriteSceneNode, "onClickAudio"));

	if (Editor::GetAttribute(spriteSceneNode, "onClickText") != NULL)
		SetUpText(Editor::GetAttributeValue(spriteSceneNode, "onClickText"));
}

void ESprite::SetUpAudio(const char* audioId) {
	onClickAudio = true;
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

void ESprite::SetUpText(const char* textId) {
	onClickText = true;
	for (auto &text : Editor::textAssets) {
		if (strcmp(text->assetId, textId) == 0) {
			if (text->instantiated > 0) {
				//if sound already exists in scene, create one more instance for current ESprite
				EText* newText = new EText(text->pNodeInAssets);
				newText->UpdateTextData(pNodeInScene); 
				pText = newText;
			}
			else {
				text->instantiated = true;
				text->UpdateTextData(pNodeInScene);
				pText = text;
			}
		}
	}
}