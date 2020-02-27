#include "EAudio.h"
#include "Editor.h"

EAudio::EAudio() {}

EAudio::EAudio(rapidxml::xml_node<>* assetNode) {
	pNodeInAssets = assetNode;
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

void EAudio::UpdateAudioData(rapidxml::xml_node<>* audioSceneNode) {
	if (Editor::GetAttribute(audioSceneNode, "volume") != NULL)
		vol = atof(Editor::GetAttributeValue(audioSceneNode, "volume"));

	if (Editor::GetAttribute(audioSceneNode, "pitch") != NULL)
		pitch = atof(Editor::GetAttributeValue(audioSceneNode, "pitch"));

	sound.setVolume(vol);
	sound.setPitch(pitch);
}

void EAudio::LoadSound() {
	if (buffer.loadFromFile(src) != NULL){
		buffer.loadFromFile(src);
		sound.setBuffer(buffer);
		sound.setVolume(vol);
		sound.setPitch(pitch);
	}
}

void EAudio::PlaySound() {
	sound.play();
}

void EAudio::LoadMusic() {
	if (music.openFromFile(src) != NULL) {
		music.openFromFile(src);
		music.setVolume(vol);
		music.setPitch(pitch);
		music.play();
	}
}