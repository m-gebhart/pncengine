#ifndef ESPRITE_H
#define ESPRITE_H

#include "Entity.h"

class ESprite : public Entity {
public:
	ESprite();
	ESprite(rapidxml::xml_node<>* spriteNode);
};
#endif