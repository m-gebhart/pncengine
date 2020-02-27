#include "Editor.h"
#include "ESprite.h"
#include "EScene.h"
#include "EText.h"

std::string Editor::assetPath = "";
std::vector<EAudio*> Editor::audioAssets;
std::vector<EText*> Editor::textAssets;
int Editor::activeSceneId = 0;
int Editor::fps = 24;
int Editor::width = 100;
int Editor::height = 100;

Editor::Editor() {}

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
	width = atoi(GetAttributeValue(currentNode, "width"));
	height = atoi(GetAttributeValue(currentNode, "height"));
	pWindow->setSize(sf::Vector2u(width, height));
	pWindow->setTitle(GetAttributeValue(currentNode, "title"));
	fps = atoi(Editor::GetAttributeValue(currentNode, "fps"));
	pWindow->setFramerateLimit(fps);
}

void Editor::LoadAssets() {
	assetPath = Editor::GetAttributeValue(pAssetsLibrary, "path");
	assetPath.append("/");
	if (assetPath.compare(0, 1, "/") == 0)
		assetPath = assetPath.substr(1, assetPath.size()-1);

	//storing the assets from AssetsLibrary, saving their data - so that the scene can access them later
	for (rapidxml::xml_node<>* assetNode = pAssetsLibrary->first_node(); assetNode != NULL; assetNode = assetNode->next_sibling())
		if (strcmp(assetNode->name(), "sprite") == 0) {
			ESprite* newSprite = new ESprite(assetNode);
			spriteAssets.push_back(newSprite);
		}
		else if (strcmp(assetNode->name(), "audio") == 0) {
			EAudio* newAudio = new EAudio(assetNode);
			audioAssets.push_back(newAudio);
		}
		else if (strcmp(assetNode->name(), "text") == 0) {
			EText* newText = new EText(assetNode);
			textAssets.push_back(newText);
		}
		else if (strcmp(assetNode->name(), "player") == 0)
			pPlayer = new EPlayer(assetNode);
}


void Editor::LoadScene(int sceneId) {
	pActiveSceneNode = Editor::GetActiveScene(sceneId);
	pActiveScene = new EScene(pActiveSceneNode);
	//loading sprite-assets (regular sprites, player) from "bottom up", according to scene's layering hierarchy
	for (rapidxml::xml_node<>* sceneAssetNode = pActiveSceneNode->last_node(); sceneAssetNode != NULL; sceneAssetNode = sceneAssetNode->previous_sibling())
		if (strcmp(sceneAssetNode->name(), "player") == 0)
			Editor::LoadPlayerIntoScene(sceneAssetNode);
		else
			Editor::LoadSpriteIntoScene(sceneAssetNode);

	//loading textAssets on Top
	Editor::LoadTextInScene(pActiveSceneNode);
}

void Editor::LoadPlayerIntoScene(rapidxml::xml_node<>* sceneAssetNode) {
	for (int i = 0; i < sizeof(pActiveScene->moveLevelLimit); i++)
		pPlayer->moveLimit[i] = pActiveScene->moveLevelLimit[i];

	pActiveScene->activeSceneSpriteAssets.push_back(pPlayer->pPlayerSprite);
	pPlayer->UpdatePlayerData(sceneAssetNode);
}

void Editor::LoadSpriteIntoScene(rapidxml::xml_node<>* sceneAssetNode) {
	const char* assetName = sceneAssetNode->name();

	//for every asset, data from nodes in scene will be applied
	for (auto &asset : Editor::spriteAssets) {
		if (strcmp(asset->assetId, assetName) == 0)
			if (asset->instantiated > 0){
				//if first instance of same assetId already exists, copy and create one more instance
				ESprite* newSprite = new ESprite(asset->pNodeInAssets);
				newSprite->UpdateSpriteData(sceneAssetNode);
				pActiveScene->activeSceneSpriteAssets.push_back(newSprite);
			}
			else {
				asset->instantiated = true;
				asset->UpdateSpriteData(sceneAssetNode);
				pActiveScene->activeSceneSpriteAssets.push_back(asset);
			}
	}
}

void Editor::LoadTextInScene(rapidxml::xml_node<>* sceneNode) {
	for (auto &asset : Editor::textAssets) {
		for (rapidxml::xml_node<>* sceneTextNode = sceneNode->first_node(); sceneTextNode != NULL; sceneTextNode = sceneTextNode->next_sibling()) {
			if (strcmp(sceneTextNode->name(), asset->assetId) == 0){
				if (asset->instantiated > 0) {
					//if first instance of same assetId already exists, copy and create one more instance
					EText* newText = new EText(asset->pNodeInAssets);
					newText->UpdateTextData(sceneTextNode);
					pActiveScene->activeSceneTextAssets.push_back(newText);
				}
				else {
					asset->instantiated = true;
					asset->UpdateTextData(sceneTextNode);
					pActiveScene->activeSceneTextAssets.push_back(asset);
				}
			}
		}
	}
}

void Editor::DrawOnWindow(){
	for (auto &asset : Editor::pActiveScene->activeSceneSpriteAssets)
		pWindow->draw(*asset->ESprite::pSprite);

	for (auto &asset : Editor::pActiveScene->activeSceneTextAssets)
		pWindow->draw(asset->EText::text);
}

rapidxml::xml_node<>* Editor::GetActiveScene(int sceneId) {
	rapidxml::xml_node<>* allScenesNode = Editor::FindChildNode(pRootNode, "scenes");
	for (rapidxml::xml_node<>* sceneNode = allScenesNode->first_node(); sceneNode != NULL; sceneNode = sceneNode->next_sibling())
		if (atoi(Editor::GetAttributeValue(sceneNode, "sceneId")) == sceneId)
			return sceneNode;
	return NULL;
}

void Editor::CheckOnClickObjects() {
	//remove text of latest onClickText()
	bool recentlyRemoved = false;
	if (pActiveScene->activeSceneTextAssets.back()->displayed > 0) {
		pActiveScene->activeSceneTextAssets.back()->displayed = false;
		pActiveScene->activeSceneTextAssets.erase(pActiveScene->activeSceneTextAssets.begin() + pActiveScene->activeSceneTextAssets.size() - 1);
		recentlyRemoved = true;
	}

	//checking each OnClickAudio and OnClickText-Reactions with MousePos
	auto clickPos = pWindow->mapPixelToCoords(sf::Mouse::getPosition(*pWindow));
	for (auto &asset : Editor::pActiveScene->activeSceneSpriteAssets) {
		if (asset->ClickedOn(clickPos)) {
			if (asset->onClickAudio > 0 && asset->pAudio != NULL)
				asset->pAudio->PlaySound();
			if (asset->onClickText > 0 && asset->pText != NULL && !asset->pText->displayed > 0 && !recentlyRemoved > 0) {
				pActiveScene->activeSceneTextAssets.push_back(asset->pText);
				asset->pText->displayed = true;
			}
		}
	}
}