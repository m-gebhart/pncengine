#include "EScene.h"
#include "Editor.h"

EScene::EScene() {}

EScene::EScene(rapidxml::xml_node<>* spriteNode) {
	sceneNode = spriteNode;
	ApplySceneData(sceneNode);
}

void EScene::ApplySceneData(rapidxml::xml_node<>* sceneNode) {
	if (Editor::GetAttribute(sceneNode, "leftLevelLimit") != NULL)
		moveLimit[0] = atoi(Editor::GetAttributeValue(sceneNode, "leftLevelLimit"));
	if (Editor::GetAttribute(sceneNode, "upperLevelLimit") != NULL)
		moveLimit[1] = atoi(Editor::GetAttributeValue(sceneNode, "upperLevelLimit"));
	if (Editor::GetAttribute(sceneNode, "righttLevelLimit") != NULL)
		moveLimit[2] = atoi(Editor::GetAttributeValue(sceneNode, "rightLevelLimit"));
	if (Editor::GetAttribute(sceneNode, "lowerLevelLimit") != NULL)
		moveLimit[3] = atoi(Editor::GetAttributeValue(sceneNode, "lowerLevelLimit"));
}