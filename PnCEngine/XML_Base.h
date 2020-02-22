#pragma once
#include "rapidxml.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct XML_Base {
	rapidxml::xml_node<>* FindChildNode(rapidxml::xml_node<>* ptr_node, const char* name);
	rapidxml::xml_attribute<>* GetAttribute(rapidxml::xml_node<>* ptr_node, const char* name);
	sf::Vector2f GetAttributeVectorValue(rapidxml::xml_node<>* ptr_node, const char* name);
	char* GetAttributeValue(rapidxml::xml_node<>* ptr_node, const char* name);
};