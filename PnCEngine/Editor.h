#pragma once

#include "ESprite.h"
#include "XML_Base.h"

class Editor : public XML_Base {
private:
	rapidxml::xml_document<>* pDoc;
	rapidxml::xml_node<>* pRootNode;
	rapidxml::xml_node<>* pActiveSceneNode;
	rapidxml::xml_node<>* pAssetsLibrary;

public:
	sf::RenderWindow* pWindow;
	std::vector<ESprite*> spriteAssets;
	std::vector<ESprite*> sceneSpriteAssets;
	static std::string assetPath;
	static int activeSceneId;

public:
	Editor();
	void LoadFile(const char file[]);
	void SetWindow();

	void LoadAssets();
	void LoadSprite(rapidxml::xml_node<>* spriteNode);
	void LoadPlayer(rapidxml::xml_node<>* spriteNode);
	void LoadAudio(rapidxml::xml_node<>* spriteNode);

	rapidxml::xml_node<>* GetActiveScene(int sceneId);
	void LoadScene(int scene);
	void SetSpriteData(rapidxml::xml_node<>* asset);
	void SetPlayerData();
	void DrawOnWindow();
};