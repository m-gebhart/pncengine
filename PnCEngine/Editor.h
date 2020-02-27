#ifndef EDITOR_H
#define EDITOR_H

#include "XML_Base.h"
#include "ESprite.h"
#include "EPlayer.h"
#include "EScene.h"
#include "EAudio.h"
#include "EText.h"

class Editor : public XML_Base {
private:
	rapidxml::xml_document<>* pDoc;
	rapidxml::xml_node<>* pRootNode;
	rapidxml::xml_node<>* pActiveSceneNode;
	rapidxml::xml_node<>* pAssetsLibrary;

public:
	sf::RenderWindow* pWindow;
	std::vector<ESprite*> spriteAssets;
	std::vector<EText*> textAssets;
	static std::vector<EAudio*> audioAssets;
	static std::string assetPath;
	static int activeSceneId;
	static int fps;
	static int width;
	static int height;
	EScene* pActiveScene;
	EPlayer* pPlayer;

public:
	Editor();
	void LoadFile(const char file[]);
	void SetWindow();

	void LoadAssets();
	rapidxml::xml_node<>* GetActiveScene(int sceneId);
	void LoadScene(int scene);
	void LoadSpriteIntoScene(rapidxml::xml_node<>* spriteAsset);
	void LoadTextInScene(rapidxml::xml_node<>* sceneNode);
	void LoadPlayerIntoScene(rapidxml::xml_node<>* playerAsset);
	void DrawOnWindow();
	void CheckOnClickObjects();
};
#endif