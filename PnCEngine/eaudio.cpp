#include "EAudio.h"
#include "Editor.h"

EAudio::EAudio() {}

EAudio::EAudio(rapidxml::xml_node<>* assetNode) {
	ApplyDefaultAssetData(assetNode);
	ApplyDefaultAudioData(assetNode);
}

void EAudio::ApplyDefaultAudioData(rapidxml::xml_node<>* audioNode) {
	if (Editor::GetAttribute(audioNode, "volume") == NULL)
		vol = 100;
	else
		vol = atof(Editor::GetAttributeValue(audioNode, "volume"));

	if (Editor::GetAttribute(audioNode, "pitch") == NULL)
		pitch = 1;
	else
		pitch = atof(Editor::GetAttributeValue(audioNode, "pitch"));
}

void EAudio::LoadAudio() {
	if (buffer.loadFromFile(src) != NULL){
		buffer.loadFromFile(src);
		sound.setBuffer(buffer);
		sound.setVolume(vol);
		sound.setPitch(pitch);
	}
}

void EAudio::PlayAudio() {
	sound.play();
}