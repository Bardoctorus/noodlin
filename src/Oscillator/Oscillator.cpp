#include "Oscillator.h"

void Oscillator::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("getNextSample"), &Oscillator::getNextSample);
	godot::ClassDB::bind_method(D_METHOD("setFrequency", "_frequency"), &Oscillator::setFrequency);
	godot::ClassDB::bind_method(D_METHOD("getFrequency"), &Oscillator::getFrequency);
	godot::ClassDB::bind_method(D_METHOD("setFrequencyMod", "_frequency"), &Oscillator::setFrequencyMod);
	godot::ClassDB::bind_method(D_METHOD("getFrequencyMod"), &Oscillator::getFrequencyMod);
	godot::ClassDB::bind_method(D_METHOD("setIncrement", "_frequency"), &Oscillator::setIncrement);
	godot::ClassDB::bind_method(D_METHOD("getIncrement"), &Oscillator::getIncrement);
	godot::ClassDB::bind_method(D_METHOD("start"), &Oscillator::start);
	godot::ClassDB::bind_method(D_METHOD("stop"), &Oscillator::stop);
	godot::ClassDB::bind_method(D_METHOD("interpolateLinearly"), &Oscillator::interpolateLinearly);
	godot::ClassDB::bind_method(D_METHOD("isCurrentlyPlaying"), &Oscillator::isCurrentlyPlaying);
	godot::ClassDB::bind_method(D_METHOD("isReadyToPlay"), &Oscillator::isReadyToPlay);
	godot::ClassDB::bind_method(D_METHOD("reset","_id", "_wavetable", "_type" "_sampleRate"), &Oscillator::reset);
}

Oscillator::Oscillator() {
	id = 0;
	type = "";
	sampleRate = 0.0f;
	index = 0.0f;
	increment = 0.0f;
	frequency = 440.0f;
	frequencyMod = 1.0f;
	amplitude = 1;
	isPlaying = false;
}

Oscillator::~Oscillator() {
}

float Oscillator::getNextSample() {
	if (isPlaying == false) {
		return 0.0f;
	} else {
		float prevIndex = index;
		index = godot::Math::fmod(index, (float)wavetable.size());
		float sample = interpolateLinearly();
		index += increment;
		return sample * amplitude;
	}
}

void Oscillator::setFrequency(float _frequency) {
	frequency = _frequency * frequencyMod;
	setIncrement(frequency);
}

float Oscillator::getFrequency() const {
	return frequency;
}

void Oscillator::setFrequencyMod(float _frequencyMod) {
	if (_frequencyMod <= 0) {
		return;
	} else {
		frequencyMod = _frequencyMod;
	}
}

float Oscillator::getFrequencyMod() const {
	return frequencyMod;
}

void Oscillator::setIncrement(float _frequency) {
	increment = _frequency * ((float)wavetable.size() / sampleRate);
}

float Oscillator::getIncrement() const {
	return increment;
}

void Oscillator::setAmplitude(float _amplitude) {
	amplitude = _amplitude;
	if (amplitude > 1.0f) {
		amplitude = 1.0f;
	}
	if (amplitude < 0.0f) {
		amplitude = 0.0f;
	}
}

float Oscillator::getAplitude() const {
	return amplitude;
}

void Oscillator::start() {
	if (readyToPlay) {
		setFrequency(frequency);
		isPlaying = true;
	} else {
		print_line("Oscillator ", id, " not ready to play");
	}
}

void Oscillator::stop() {
	isPlaying = false;
	index = 0.0f;
	increment = 0.0f;
}

float Oscillator::interpolateLinearly() {
	int truncatedIndex = floor(index);
	int nextIndex = (int)ceil(index) % wavetable.size();
	float nextIndexWeight = index - (float)truncatedIndex;
	float nextWave = wavetable[nextIndex];
	float trucWave = wavetable[truncatedIndex];
	return nextWave * nextIndexWeight + (1 - nextIndexWeight) * trucWave;
}

bool Oscillator::isCurrentlyPlaying() const {
	return isPlaying;
}

bool Oscillator::isReadyToPlay() {
	return readyToPlay;
}

void Oscillator::reset(int _id, Array _wavetable, String _type, float _sampleRate) {
	// if we are going to allow sample rate changes we need to check for it here
	// and remake wavetables
	// something like if sampleRate != _samplerate newWavetables(_sampleRate)
	stop();
	readyToPlay = false;
	id = _id;
	wavetable = _wavetable;
	type = _type;
	sampleRate = _sampleRate;
	frequency = 440.0f;
	readyToPlay = true;
	//print_line("osc reset wavetable: ", wavetable);
}
