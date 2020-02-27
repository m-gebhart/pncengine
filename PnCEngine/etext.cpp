#include "EText.h"
#include "Editor.h"

EText::EText() {}

EText::EText(rapidxml::xml_node<>* textNode) {
	pNodeInAssets = textNode;
	ApplyDefaultAssetData(textNode);
	ApplyDefaultTextData(textNode);

	EText::SetContent(content);
	text.setCharacterSize(size);
	text.setFont(font);
	EText::SetPosition(pos);
}

void EText::SetPosition(sf::Vector2f newPos) {
	pos = newPos;
	text.setPosition(newPos.x, newPos.y);
}

void EText::SetContent(std::string newContent) {
	content = newContent;
	text.setString(content);
}

void EText::ApplyDefaultTextData(rapidxml::xml_node<>* textNode) {
	font.loadFromFile(src);

	if (textNode->value() == NULL)
		content = "[missing]";
	else
		content = textNode->value();


	if (Editor::GetAttribute(textNode, "size") == NULL)
		size = 15;
	else
		size = atoi(Editor::GetAttributeValue(textNode, "size"));
}

void EText::UpdateTextData(rapidxml::xml_node<>* sceneTextNode) {
	if (sceneTextNode->value_size() > 0)
		EText::SetContent(sceneTextNode->value());

	if (Editor::GetAttribute(sceneTextNode, "textPosition") != NULL)
		EText::SetPosition(Editor::GetAttributeVector2fValue(sceneTextNode, "textPosition"));
	else if (Editor::GetAttribute(sceneTextNode, "position") != NULL)
		EText::SetPosition(Editor::GetAttributeVector2fValue(sceneTextNode, "position"));

	if (Editor::GetAttribute(sceneTextNode, "size") != NULL) {
		size = atoi(Editor::GetAttributeValue(sceneTextNode, "size"));
		text.setCharacterSize(size);
	}

	if (Editor::GetAttribute(sceneTextNode, "src") != NULL) {
		font.loadFromFile(src);
		text.setFont(font);
	}
}