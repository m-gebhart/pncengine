#ifndef EAUDIO_H
#define EAUDIO_H

#include "Entity.h"

class EAudio : public Entity {
	sf::SoundBuffer buffer;
public:
	sf::Sound sound;
	float vol;
	float pitch;

	EAudio();
	EAudio(rapidxml::xml_node<>* audioNode);
	void ApplyDefaultAudioData(rapidxml::xml_node<>* audioNode);
	void LoadAudio();
	void PlayAudio();
};
#endif