#pragma once

#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/audio_stream_generator_playback.hpp"
#include "CppWavetableOscillator.h"

using namespace godot;

#define WAVETABLE_LENGTH 64




class CppWavetableSynth: public RefCounted {
    GDCLASS(CppWavetableSynth, RefCounted);

    protected:
        static void _bind_methods();

    public:
        CppWavetableSynth();
        ~CppWavetableSynth() = default;
        void handleInput(bool message);
        void updateFrequency(float _frequency);
        void render(Ref<AudioStreamGeneratorPlayback> playback);
        void initOscillators(float _sampleRate, float _startingFreq, Array waveTable, int numOscillators);


    private:
       // Ref<CppWavetableOscillator> oscillator;
        Ref<CppWavetableOscillator> osc;
        Array oscillators;

};

