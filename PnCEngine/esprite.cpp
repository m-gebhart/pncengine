#include "Editor.h"
#include "ESprite.h"

Editor editor;

ESprite::ESprite() {
}

ESprite::ESprite(rapidxml::xml_node<>* spriteNode) {
	//applying default values
	pos.x = 0;
	pos.y = pos.x;
	pSprite = new sf::Sprite();
	pTexture = new sf::Texture();
	assetId = editor.GetAttributeValue(spriteNode, "id");
	src = Editor::assetPath + editor.GetAttributeValue(spriteNode, "src");

	pTexture->loadFromFile(src);
	pSprite->setTexture(*pTexture);
	pSprite->setPosition(pos.x, pos.y);
}