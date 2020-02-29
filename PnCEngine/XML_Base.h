#ifndef XML_BASE_H
#define XML_BASE_H

#include "rapidxml.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct XML_Base {
	static rapidxml::xml_node<>* FindChildNode(rapidxml::xml_node<>* pNode, const char* name);
	static rapidxml::xml_attribute<>* GetAttribute(rapidxml::xml_node<>* pNode, const char* name);
	static sf::Vector2i GetAttributeVector2iValue(rapidxml::xml_node<>* pNode, const char* name);
	static sf::Vector2f GetAttributeVector2fValue(rapidxml::xml_node<>* pNode, const char* name);
	static std::string GetStringVectorValue(rapidxml::xml_node<>* pNode, const char* name);
	static char* GetAttributeValue(rapidxml::xml_node<>* pNode, const char* name);
	static std::vector<int> GetAttributeVector4iValue(rapidxml::xml_node<>* pNode, const char* name);
};
#endif