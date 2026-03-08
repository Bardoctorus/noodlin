#pragma once

#include "godot_cpp/classes/audio_stream_generator_playback.hpp"
#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/node2d.hpp"


#include "DataGen/WavetableGen.h"
#include "Oscillator/Oscillator.h"

using namespace godot;

class BaseController : public RefCounted {
	GDCLASS(BaseController, RefCounted)

protected:
	static void _bind_methods();
	Array oscillators;
	float amplitude;
	float frequency;
	bool currentlyPlaying;

	Array customWavetable;
	PackedVector2Array buffer;

	Dictionary wavetables;
    // caching the strings to stop typos in dict lookups
    String Sine;
    String SawUp;
    String SawDown;
    String Square;
    String Triangle;
    String DetuneAmount;
    String LFOFreq;
    String LFOAmount;


public:
	BaseController();
	~BaseController();

	//this also needs rethinking from the godot side. It'd be nice to send in a config struct
	//or I guess refcounted data object that can setup all the wavetables needed and assign them
	// to the oscillators and LFOs
	void init(float _sampleRate, Array voices);

	void update(float _sampleRate, Array voices);

	float getAmplitude() const;
	void setAmplitude(float _amplitude);
	float getFrequency() const;
	void setFrequency(float _frequency);
	//this is ugly and prone to fuckups - some kind of key pair thing might be better here
	void updateModifiers(Dictionary modifiers);
	bool isCurrentlyPlaying() const;
	void start();
	void stop();

	void process(Ref<AudioStreamGeneratorPlayback> playback);
	Ref<WavetableGen> wavetableGen;
};