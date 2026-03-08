#pragma once

#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/ref_counted.hpp"


using namespace godot;

class Oscillator : public RefCounted {
    GDCLASS(Oscillator, RefCounted)

    protected:
        static void _bind_methods();

    public:
        Oscillator();
        ~Oscillator();

        float getNextSample();
        void setFrequency(float _frequency);
        float getFrequency() const;
        void setIncrement(float _increment);
        float getIncrement() const;
        void setAmplitude(float _amplitude);
        float getAplitude() const;
        void start();
        void stop();
        float interpolateLinearly();
        bool isCurrentlyPlaying() const;
        bool isReadyToPlay();
        //refactor this when you have proper types
        void reset(int _id, Array _waveTable, int _type, float _sampleRate);




    private:
        int id;    
        int type;
        Array wavetable;
        float sampleRate;
        float index;
        float increment;
        float frequency;
        float frequencyMod;
        float amplitude;
        bool isPlaying;
        bool readyToPlay;

};