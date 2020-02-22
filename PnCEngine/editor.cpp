#include "Editor.h"
#include "ESprite.h"

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
	pWindow->setSize(sf::Vector2u(atoi(GetAttribute(currentNode, "width")->value()), atoi(GetAttribute(currentNode, "height")->value())));
	pWindow->setTitle(GetAttribute(currentNode, "title")->value());
	pWindow->setFramerateLimit(atoi(GetAttribute(currentNode, "fps")->value()));
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
		else if (strcmp(assetNode->name(), "player"))
			LoadPlayer(assetNode);
		else if (strcmp(assetNode->name(), "audio"))
			LoadAudio(assetNode);
}

void Editor::LoadSprite(rapidxml::xml_node<>* spriteNode) {
	ESprite* newSprite = new ESprite(spriteNode);
	spriteAssets.push_back(newSprite);
}

void Editor::LoadPlayer(rapidxml::xml_node<>* spriteNode) {}
void Editor::LoadAudio(rapidxml::xml_node<>* spriteNode) {}


void Editor::LoadScene(int sceneId) {
	pActiveSceneNode = Editor::GetActiveScene(sceneId);
	//loading assets from "bottom up" to maintain layering hierarchy
	for (rapidxml::xml_node<>* sceneAssetNode = pActiveSceneNode->last_node(); sceneAssetNode != NULL; sceneAssetNode = sceneAssetNode->previous_sibling())
		if (strcmp(sceneAssetNode->name(), "player") != 0)
			Editor::SetSpriteData(sceneAssetNode);
		else
			Editor::SetPlayerData();
}

//for every asset, the data from the scene will be applied
void Editor::SetSpriteData(rapidxml::xml_node<>* sceneAssetNode) {
	const char* assetId = sceneAssetNode->name();

	for (auto &asset : Editor::spriteAssets) {
		if (strcmp(asset->assetId, assetId) == 0) {
			if (Editor::GetAttribute(sceneAssetNode, "position") != NULL) {
				asset->pos = GetAttributeVectorValue(sceneAssetNode, "position");
				asset->pSprite->setPosition(asset->pos.x, asset->pos.y);
			}

			if (Editor::GetAttribute(sceneAssetNode, "scale") != NULL) {
				asset->scale = GetAttributeVectorValue(sceneAssetNode, "scale");
				asset->pSprite->setScale(asset->scale.x, asset->scale.y);
			}

			if (Editor::GetAttribute(sceneAssetNode, "rotation") != NULL) {
				asset->rot = atoi(GetAttributeValue(sceneAssetNode, "rotation"));
				asset->pSprite->setRotation(asset->rot);
			}

			sceneSpriteAssets.push_back(asset);
		}
	}

}

void Editor::SetPlayerData() {}

void Editor::DrawOnWindow(){
	for (auto &asset : Editor::sceneSpriteAssets) {
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