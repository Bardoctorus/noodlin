#pragma once

#include "godot_cpp/classes/ref_counted.hpp"

using namespace godot;

class SynthBuilder : public RefCounted {
	GDCLASS(SynthBuilder, RefCounted)

protected:
	static void _bind_methods();
    float sampleRate;
    Array Voices;
    Array VoiceWeights;
    Array LFOs;
    String Sine;
    String SawUp;
    String SawDown;
    String Square;
    String Triangle;
    String DetuneAmount;
    String LFOFreq;
    String LFOAmount;
     

public:
    SynthBuilder();
    ~SynthBuilder();
    void setSampleRate (float _sampleRate);
    float getSampleRate() const;
    void setVoices(Array _voices);
    Array getVoices() const;
    void setVoiceWeights(Array _voiceweights);
    Array getVoiceWeights() const;

    void addVoice(String voice, float weight = 1.0f);


};