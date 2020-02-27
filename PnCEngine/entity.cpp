#include "Entity.h"
#include "Editor.h"

void Entity::ApplyDefaultAssetData(rapidxml::xml_node<>* spriteNode) {
	//applying default values from node in assets
	if (Editor::GetAttribute(spriteNode, "position") == NULL) {
		pos.x = 0;
		pos.y = pos.x;
	}
	else
		pos = Editor::GetAttributeVector2fValue(spriteNode, "position");

	if (Editor::GetAttribute(spriteNode, "scale") == NULL) {
		scale.x = 1;
		scale.y = scale.x;
	}
	else
		scale = Editor::GetAttributeVector2fValue(spriteNode, "scale");

	if (Editor::GetAttribute(spriteNode, "origin") == NULL) {
		ori.x = 1;
		ori.y = ori.x;
	}
	else
		ori = Editor::GetAttributeVector2fValue(spriteNode, "origin");

	if (Editor::GetAttribute(spriteNode, "rotation") == NULL)
		rot = 0;
	else
		rot = atoi(Editor::GetAttributeValue(spriteNode, "rotation"));

	if (Editor::GetAttribute(spriteNode, "id") != NULL)
		assetId = Editor::GetAttributeValue(spriteNode, "id");
	
	if (Editor::GetAttribute(spriteNode, "src") != NULL)
		src = Editor::assetPath + Editor::GetAttributeValue(spriteNode, "src");
}