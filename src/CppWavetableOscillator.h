#pragma once

#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/ref_counted.hpp"


using namespace godot;

class CppWavetableOscillator : public RefCounted {
    GDCLASS(CppWavetableOscillator, RefCounted)

    protected:
        static void _bind_methods();

    public:
        CppWavetableOscillator();
        ~CppWavetableOscillator() = default;

        float getSample();
        void setFrequency(float _frequency);
        float getFrequency() const;
        void setIncrement(float _increment);
        float getIncrement() const;
        void start();
        void stop();
        void update(float _frequency);
        float interpolateLiniarly();
        void _init(Array _waveTable, float _sampleRate, float _frequency, float _detuneMult);
        bool currentlyPlaying();
        void setDetune(int oscNum, int oscCount, float detuneAmount);
        void setLfoFreqOffset(float amount);
    private:
        Array waveTable;
        float sampleRate;
        float index;
        float increment;
        float frequency;
        bool isPlaying;
        float detune;
        float lfoFreqOffset;
        float detuneMultiplyer;


};