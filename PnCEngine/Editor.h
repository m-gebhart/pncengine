#ifndef EDITOR_H
#define EDITOR_H

#include "XML_Base.h"
#include "ESprite.h"
#include "EPlayer.h"
#include "EScene.h"

class Editor : public XML_Base {
private:
	rapidxml::xml_document<>* pDoc;
	rapidxml::xml_node<>* pRootNode;
	rapidxml::xml_node<>* pActiveSceneNode;
	rapidxml::xml_node<>* pAssetsLibrary;

public:
	sf::RenderWindow* pWindow;
	std::vector<ESprite*> spriteAssets;
	static std::string assetPath;
	static int activeSceneId;
	EScene* pActiveScene;
	EPlayer* pPlayer;

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
#endif