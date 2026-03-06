#pragma once

#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/audio_stream_generator_playback.hpp"
#include "CppWavetableOscillator.h"
#include "ADSR.h"
#include "LFO.h"


using namespace godot;

#define WAVETABLE_LENGTH 64




class CppWavetableSynth: public RefCounted {
    GDCLASS(CppWavetableSynth, RefCounted);

    protected:
        static void _bind_methods();

    public:
        CppWavetableSynth();
        ~CppWavetableSynth() = default;
        void isPlaying(bool message);
        void gateTriggered(bool message);
        void updateFrequency(float _frequency);
        void updateLfoFrequency(float _frequency);

        void updateDetune(float _detuneAmount);
        void updateAmplitude(float _amplitude);
        void updateLfoAmount(float _amplitude);
        void render(Ref<AudioStreamGeneratorPlayback> playback);
        void initOscillators(float _sampleRate, float _startingFreq, int type, int numOscillators, float _detuneMult);
        Ref<CppWavetableOscillator> osc1;
        Ref<CppWavetableOscillator> osc2;
        Ref<ADSR> adsr;
        Ref<LFO> lfo;
        void updateAttack(float val);
        void updateDecay(float val);
        void updateSustain(float val);
        void updateRelease(float val);
        

    private:
       // Ref<CppWavetableOscillator> oscillator;
        
        float amplitude;
        float lfoAmount;
        float centerFreq;
        Array oscillators;
        

};

