#pragma once

#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/audio_stream_generator_playback.hpp"

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

        Array sineWavetable;
        Array sawUpWavetable;
        Array sawDownWavetable;
        Array squareWavetable;
        Array triangleWavetable;
        Array customWavetable;
        PackedVector2Array buffer;








    public:
        BaseController();
        ~BaseController();

        //this also needs rethinking from the godot side. It'd be nice to send in a config struct
        //or I guess refcounted data object that can setup all the wavetables needed and assign them
        // to the oscillators and LFOs
        void init(float _sampleRate, int _wavetableType, int _numOscillators);
        void update(float _sampleRate, int _wavetableType, int _numOscillators);

        float getAmplitude() const;
        void setAmplitude(float _amplitude);
        float getFrequency() const;
        void setFrequency(float _frequency);
        //this is ugly and prone to fuckups - some kind of key pair thing might be better here
        void updateModifiers(float _detune = 0.0f, float _lfoRate = 0.0f, float _lfoAmount = 0.0f);
        bool isCurrentlyPlaying() const;
        void start();
        void stop();

        void process(Ref<AudioStreamGeneratorPlayback> playback);
        Ref<WavetableGen> wavetableGen;



};