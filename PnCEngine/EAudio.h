#ifndef EAUDIO_H
#define EAUDIO_H

#include "Entity.h"

class EAudio : public Entity {
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Music music;
	float vol;
	float pitch;
public:
	rapidxml::xml_node<>* pNodeInAssets;

	EAudio();
	EAudio(rapidxml::xml_node<>* audioNode);
	void ApplyDefaultAudioData(rapidxml::xml_node<>* audioNode);
	void UpdateAudioData(rapidxml::xml_node<>* audioNode);
	void LoadSound();
	void PlaySound();
	void LoadMusic();
};
#endif