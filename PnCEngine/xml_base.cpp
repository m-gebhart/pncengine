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

sf::Vector2i XML_Base::GetAttributeVector2iValue(rapidxml::xml_node<>* pNode, const char* name) {
	if (XML_Base::GetAttribute(pNode, name) == NULL)
		return sf::Vector2i(0, 0);

	std::string fullValue = XML_Base::GetStringVectorValue(pNode, name);

	return sf::Vector2i (atoi(fullValue.substr(0, fullValue.find(",")).c_str()),
		atoi(fullValue.substr(fullValue.find(",") + 2, fullValue.size()).c_str()));
}

sf::Vector2f XML_Base::GetAttributeVector2fValue(rapidxml::xml_node<>* pNode, const char* name) {
	if (XML_Base::GetAttribute(pNode, name) == NULL)
		return sf::Vector2f(0, 0);

	std::string fullValue = XML_Base::GetStringVectorValue(pNode, name);

	return sf::Vector2f(atof(fullValue.substr(0, fullValue.find(",")).c_str()),
		atof(fullValue.substr(fullValue.find(",") + 2, fullValue.size()).c_str()));
}

std::string XML_Base::GetStringVectorValue(rapidxml::xml_node<>* pNode, const char* name) {
	for (rapidxml::xml_attribute<>* pAttr = pNode->first_attribute(); pAttr != NULL; pAttr = pAttr->next_attribute())
		if (strcmp(pAttr->name(), name) == 0)
			return pAttr->value();
	return "";
}

std::vector<int> XML_Base::GetAttributeVector4iValue(rapidxml::xml_node<>* pNode, const char* name) {
	std::vector<int> tempVector;
	for (int i = 0; i < 4; i++)
		tempVector.push_back(0);

	if (XML_Base::GetAttribute(pNode, name) != NULL) {
		int pos = 0;
		std::string value = XML_Base::GetAttributeValue(pNode, name);
		std::string str = std::string(name);
		while ((pos = str.find(",")) != NULL && pos < sizeof(str)) {
			value = str.substr(0, pos);
			tempVector.push_back(stoi(value));
			str.erase(0, pos + 2);
		}
	}
	return tempVector;
}

rapidxml::xml_node<>* XML_Base::FindChildNode(rapidxml::xml_node<>* pNode, const char* name) {
	//by Markus H.
	for (rapidxml::xml_node<>* pChildNode = pNode->first_node(); pChildNode != NULL; pChildNode = pChildNode->next_sibling())
		if (strcmp(pChildNode->name(), name) == 0)
			return pChildNode;
	return NULL;
}