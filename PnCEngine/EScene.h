#ifndef ESCENE_H
#define ESCENE_H

#include "Entity.h"
#include "ESprite.h"

class EScene : public Entity {
public:
	rapidxml::xml_node<>* sceneNode;
	std::vector<ESprite*> activeSceneAssets;
	int moveLevelLimit[4];

	EScene();
	EScene(rapidxml::xml_node<>* spriteNode);

	void ApplySceneData(rapidxml::xml_node<>* sceneNode);
};
#endif