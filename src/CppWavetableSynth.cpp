
#include "CppWavetableSynth.h"
#include "godot_cpp/core/math.hpp"
#include "godot_cpp/classes/audio_stream_generator_playback.hpp"




 void CppWavetableSynth::_bind_methods(){
    godot::ClassDB::bind_method(D_METHOD("handleInput", "message"), &CppWavetableSynth::handleInput);
    godot::ClassDB::bind_method(D_METHOD("updateFrequency", "_frequency"), &CppWavetableSynth::updateFrequency);
    godot::ClassDB::bind_method(D_METHOD("render", "playback"), &CppWavetableSynth::render);

    godot::ClassDB::bind_method(D_METHOD("initOscillators", "_sampleRate", "_startingFreq", "waveTable","numOscillators"), &CppWavetableSynth::initOscillators);




 }


CppWavetableSynth::CppWavetableSynth(){

};





void CppWavetableSynth::initOscillators(float _sampleRate, float _startingFreq, Array waveTable, int numOscillators) {
    // you are doing this wrong - you need to memnew, or memnew_arr
    for (size_t i = 0; i < numOscillators; i++)
    {
        oscillator.instantiate();
        oscillator->_init(waveTable, _sampleRate, _startingFreq);
        oscillators.push_back(oscillator);
        print_line("Oscillator: ", oscillator->get_instance_id());
    }

    
}


void CppWavetableSynth::handleInput(bool message){
    if (message == true){
        for (size_t i = 0; i < oscillators.size(); i++)
        {
            oscillators[i].call("start");
        }
        
            
    }
    else{
        for (size_t i = 0; i < oscillators.size(); i++)
        {
            oscillator->stop();
        }
    }
}
void CppWavetableSynth::updateFrequency(float _frequency){
    print_line("update freq: %s", _frequency);
    for (size_t i = 0; i < oscillators.size(); i++)
        {
            oscillator->update(_frequency);
        }
}

void CppWavetableSynth::render(Ref<AudioStreamGeneratorPlayback> playback){
    for (size_t i = 0; i < oscillators.size(); i++)
    {
        if (oscillator->currentlyPlaying())
        {
            PackedVector2Array buffer;
            for (int i = 0; i < playback->get_frames_available(); ++i)
            {
                float sample = oscillator->getSample();
            // playback->push_frame(Vector2(sample, sample)); // actually slower in c++ according to docs
            buffer.push_back(Vector2(sample, sample));
            }
            playback->push_buffer(buffer);
        }
       }
}

