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