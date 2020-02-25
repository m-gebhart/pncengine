#include "Editor.h"
#include "ESprite.h"
#include "EScene.h"

std::string Editor::assetPath = "";
int Editor::activeSceneId = 0;

Editor::Editor() {
}

void Editor::LoadFile(const char file[]) {
	std::ifstream gameData(file, std::ios::binary);
	gameData.seekg(0, std::ios::end);
	std::streampos end = gameData.tellg();
	int nSize = end;
	gameData.seekg(0, std::ios::beg);

	char* int_parse = new char[nSize + 1];
	memset(int_parse, 0, nSize + 1);
	gameData.read(int_parse, nSize);
	gameData.close();

	rapidxml::xml_document<> document;
	pDoc = &document;
	pDoc->parse<0>(int_parse);
	pRootNode = pDoc->first_node();
	pAssetsLibrary = Editor::FindChildNode(pRootNode, "assets");
	activeSceneId = atoi(Editor::GetAttributeValue(pRootNode, "entryScene"));
	pActiveSceneNode = GetActiveScene(activeSceneId);

	SetWindow();
}

void Editor::SetWindow() {
	rapidxml::xml_node<>* currentNode = pRootNode;
	pWindow->setSize(sf::Vector2u(atoi(GetAttributeValue(currentNode, "width")), atoi(GetAttributeValue(currentNode, "height"))));
	pWindow->setTitle(GetAttributeValue(currentNode, "title"));
	pWindow->setFramerateLimit(atoi(GetAttributeValue(currentNode, "fps")));
}

void Editor::LoadAssets() {
	assetPath = Editor::GetAttributeValue(pAssetsLibrary, "path");
	assetPath.append("/");
	if (assetPath.compare(0, 1, "/") == 0)
		assetPath = assetPath.substr(1, assetPath.size()-1);

	//storing the assets from AssetsLibrary, saving their data - so that the scene can access them later
	for (rapidxml::xml_node<>* assetNode = pAssetsLibrary->first_node(); assetNode != NULL; assetNode = assetNode->next_sibling())
		if (strcmp(assetNode->name(), "sprite")==0)
			LoadSprite(assetNode);
		else if (strcmp(assetNode->name(), "player")==0)
			LoadPlayer(assetNode);
		else if (strcmp(assetNode->name(), "audio")==0)
			LoadAudio(assetNode);
}

void Editor::LoadSprite(rapidxml::xml_node<>* spriteNode) {
	ESprite* newSprite = new ESprite(spriteNode);
	spriteAssets.push_back(newSprite);
}

void Editor::LoadPlayer(rapidxml::xml_node<>* spriteNode) {
	pPlayer = new EPlayer(spriteNode);
}

void Editor::LoadAudio(rapidxml::xml_node<>* spriteNode) {}


void Editor::LoadScene(int sceneId) {
	pActiveSceneNode = Editor::GetActiveScene(sceneId);
	pActiveScene = new EScene(pActiveSceneNode);
	//loading assets to scene from "bottom up", according to scene's layering hierarchy
	for (rapidxml::xml_node<>* sceneAssetNode = pActiveSceneNode->last_node(); sceneAssetNode != NULL; sceneAssetNode = sceneAssetNode->previous_sibling())
		if (strcmp(sceneAssetNode->name(), "player") == 0)
			Editor::SetPlayerData();
		else
			Editor::SetSpriteData(sceneAssetNode);
}

void Editor::SetSpriteData(rapidxml::xml_node<>* sceneAssetNode) {
	const char* assetName = sceneAssetNode->name();

	//for every asset, the data from the scene will be applied
	for (auto &asset : Editor::spriteAssets) {
		if (strcmp(asset->assetId, assetName) == 0) {
			asset->UpdateAssetData(sceneAssetNode);
			pActiveScene->activeSceneAssets.push_back(asset);
		}
	}
}

void Editor::SetPlayerData() {
	pActiveScene->activeSceneAssets.push_back(pPlayer->pPlayerSprite);
}

void Editor::DrawOnWindow(){
	for (auto &asset : Editor::pActiveScene->activeSceneAssets) {
		pWindow->draw(*asset->ESprite::pSprite);
	}
}

rapidxml::xml_node<>* Editor::GetActiveScene(int sceneId) {
	rapidxml::xml_node<>* allScenesNode = Editor::FindChildNode(pRootNode, "scenes");
	for (rapidxml::xml_node<>* sceneNode = allScenesNode->first_node(); sceneNode != NULL; sceneNode = sceneNode->next_sibling())
		if (atoi(Editor::GetAttributeValue(sceneNode, "sceneId")) == sceneId)
			return sceneNode;
	return NULL;
}