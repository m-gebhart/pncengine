#include "ESprite.h"
#include "Editor.h"

ESprite::ESprite() {}

ESprite::ESprite(rapidxml::xml_node<>* spriteNode) {	
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

void ESprite::UpdateSpriteData(rapidxml::xml_node<>* spriteNode) {
	UpdateAssetData(spriteNode);

	if (Editor::GetAttribute(spriteNode, "onClickAudio") != NULL)
		SetUpAudio(Editor::GetAttributeValue(spriteNode, "onClickAudio"));
}

void ESprite::SetUpAudio(const char* audioData) {
	onClickAction = true;
	for (auto &audio : Editor::audioAssets) {
		if (strcmp(audio->assetId, audioData) == 0) {
			audio->LoadAudio();
			pAudio = audio;
		}
	}
}

bool ESprite::ClickedOn(sf::Vector2f clickPos) {
	if (pSprite->getGlobalBounds().contains(clickPos))
		return true;
	return false;
}