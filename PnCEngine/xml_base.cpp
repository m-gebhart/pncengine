#include "XML_Base.h"

rapidxml::xml_attribute<>* XML_Base::GetAttribute(rapidxml::xml_node<>* pNode, const char* name) {
	//by Markus H.
	for (rapidxml::xml_attribute<>* pAttr = pNode->first_attribute(); pAttr != NULL; pAttr = pAttr->next_attribute())
		if (strcmp(pAttr->name(), name) == 0)
			return pAttr;
	return NULL;
}

char* XML_Base::GetAttributeValue(rapidxml::xml_node<>* pNode, const char* name) {
	return XML_Base::GetAttribute(pNode, name)->value();
}

sf::Vector2f XML_Base::GetAttributeVectorValue(rapidxml::xml_node<>* pNode, const char* name) {
	if (XML_Base::GetAttribute(pNode, name) == NULL)
		return sf::Vector2f(0, 0);

	std::string fullValue = "";
	for (rapidxml::xml_attribute<>* pAttr = pNode->first_attribute(); pAttr != NULL; pAttr = pAttr->next_attribute())
		if (strcmp(pAttr->name(), name) == 0)
			fullValue = pAttr->value();

	return sf::Vector2f (atoi(fullValue.substr(0, fullValue.find(",")).c_str()),
		atoi(fullValue.substr(fullValue.find(",") + 2, fullValue.size()).c_str()));
}

rapidxml::xml_node<>* XML_Base::FindChildNode(rapidxml::xml_node<>* pNode, const char* name) {
	//by Markus H.
	for (rapidxml::xml_node<>* pChildNode = pNode->first_node(); pChildNode != NULL; pChildNode = pChildNode->next_sibling())
		if (strcmp(pChildNode->name(), name) == 0)
			return pChildNode;
	return NULL;
}