#ifndef ESCENE_H
#define ESCENE_H

#include "Entity.h"
#include "ESprite.h"
#include "EAudio.h"

class EScene : public Entity {
	EAudio* pMusic;

public:
	rapidxml::xml_node<>* sceneNode;
	std::vector<ESprite*> activeSceneAssets;
	int moveLevelLimit[4];

	EScene();
	EScene(rapidxml::xml_node<>* spriteNode);
	void ApplySceneData(rapidxml::xml_node<>* sceneNode);
	void SetUpMusic(const char* musicData);
};
#endif