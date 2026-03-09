#include "SynthBuilder.h"

void SynthBuilder::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("setSampleRate", "_sampleRate"), &SynthBuilder::setSampleRate);
	godot::ClassDB::bind_method(D_METHOD("getSampleRate"), &SynthBuilder::getSampleRate);
	godot::ClassDB::bind_method(D_METHOD("setVoices", "_voices"), &SynthBuilder::setVoices);
	godot::ClassDB::bind_method(D_METHOD("getVoices"), &SynthBuilder::getVoices);
	godot::ClassDB::bind_method(D_METHOD("setVoiceWeights", "_voiceweights"), &SynthBuilder::setVoiceWeights);

	godot::ClassDB::bind_method(D_METHOD("getVoiceWeights"), &SynthBuilder::getVoiceWeights);

	godot::ClassDB::bind_method(D_METHOD("addVoice", "voice", "weight"), &SynthBuilder::addVoice);
}

SynthBuilder::SynthBuilder() {
	Sine = "Sine";
	SawUp = "SawUp";
	SawDown = "SawDown";
	Square = "Square";
	Triangle = "Triangle";
	DetuneAmount = "DetuneAmount";
	LFOFreq = "LFOFreq";
	LFOAmount = "LFOAmount";
}

SynthBuilder::~SynthBuilder() {
}

void SynthBuilder::setSampleRate(float _sampleRate) {
	sampleRate = _sampleRate;
}

float SynthBuilder::getSampleRate() const {
	return sampleRate;
}

void SynthBuilder::setVoices(Array _voices) {
	Voices.clear();
	for (size_t i = 0; i < _voices.size(); i++) {
		Voices[i] = _voices[i];
	}
}

Array SynthBuilder::getVoices() const {
	return Voices;
}

void SynthBuilder::setVoiceWeights(Array _voiceweights) {
	VoiceWeights.clear();
	for (size_t i = 0; i < _voiceweights.size(); i++) {
		VoiceWeights[i] = _voiceweights[i];
	}
}

Array SynthBuilder::getVoiceWeights() const {
	return Array();
}

void SynthBuilder::addVoice(String voice, float weight) {
	Voices.append(voice);
	VoiceWeights.append(weight);
}
