#include "EScene.h"
#include "Editor.h"

EScene::EScene() {}

EScene::EScene(rapidxml::xml_node<>* spriteNode) {
	sceneNode = spriteNode;
	ApplySceneData(spriteNode);
}

void EScene::ApplySceneData(rapidxml::xml_node<>* sceneNode) {
	if (Editor::GetAttribute(sceneNode, "leftLevelLimit") != NULL)
		moveLevelLimit[0] = atoi(Editor::GetAttributeValue(sceneNode, "leftLevelLimit"));
	else
		moveLevelLimit[0] = 0;

	if (Editor::GetAttribute(sceneNode, "upperLevelLimit") != NULL)
		moveLevelLimit[1] = atoi(Editor::GetAttributeValue(sceneNode, "upperLevelLimit"));
	else
		moveLevelLimit[1] = 0;
	
	if (Editor::GetAttribute(sceneNode, "rightLevelLimit") != NULL)
		moveLevelLimit[2] = atoi(Editor::GetAttributeValue(sceneNode, "rightLevelLimit"));
	else
		moveLevelLimit[2] = Editor::width;
	
	if (Editor::GetAttribute(sceneNode, "lowerLevelLimit") != NULL)
		moveLevelLimit[3] = atoi(Editor::GetAttributeValue(sceneNode, "lowerLevelLimit"));
	else
		moveLevelLimit[3] = Editor::height;

	if (Editor::GetAttribute(sceneNode, "music") != NULL) {
		SetUpMusic(Editor::GetAttributeValue(sceneNode, "music"));
	}
}

void EScene::SetUpMusic(const char* musicData) {
	for (auto &audio : Editor::audioAssets) {
		if (strcmp(audio->assetId, musicData) == 0) {
			audio->UpdateAudioData(sceneNode);
			audio->LoadMusic();
			pMusic = audio;
		}
	}
}