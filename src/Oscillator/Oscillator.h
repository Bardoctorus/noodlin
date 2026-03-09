#pragma once

#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/ref_counted.hpp"


using namespace godot;

//dirty freq clamp values
#define MAXFREQ 150000.0f
#define MINFREQ 20.0f

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
        void setFrequencyMod(float _frequencyMod);
        float getFrequencyMod() const;
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
        void reset(int _id, Array _waveTable, String _type, float _sampleRate);




    private:
        int id;    
        String type;
        Array wavetable;
        float sampleRate;
        float index;
        float increment;
        float frequency;
        float frequencyMod;
        float amplitude;
        float amplitudeMod;
        bool isPlaying;
        bool readyToPlay;
      

};