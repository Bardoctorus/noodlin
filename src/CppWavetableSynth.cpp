
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
    for (size_t i = 0; i < numOscillators; i++)
    {
        
        Ref<CppWavetableOscillator> thosk;
        thosk.instantiate();
        thosk->_init(waveTable, _sampleRate, _startingFreq);
        print_line("Oscillator instantiated with id: ",thosk->get_instance_id());
        oscillators.push_back(thosk);

    }

    
}




void CppWavetableSynth::handleInput(bool message){

    
    // for (size_t i = 0; i < oscillators.size(); i++)
    // {

    //     Ref<CppWavetableOscillator> hop = Ref<CppWavetableOscillator>(Object::cast_to<CppWavetableOscillator>(oscillators[i]));
    //     print_line(hop->get_instance_id());
    // }
    
    
    if (message == true){
       
            
       for (size_t i = 0; i < oscillators.size(); i++)
    {

        Ref<CppWavetableOscillator> hop = Ref<CppWavetableOscillator>(Object::cast_to<CppWavetableOscillator>(oscillators[i]));
        hop->start();
    }

            
    }
    else{
        for (size_t i = 0; i < oscillators.size(); i++)
        {
            Ref<CppWavetableOscillator> hop = Ref<CppWavetableOscillator>(Object::cast_to<CppWavetableOscillator>(oscillators[i]));
            hop->stop();
        }
    }
}
void CppWavetableSynth::updateFrequency(float _frequency){
    print_line("update freq: %s", _frequency);
    for (size_t i = 0; i < oscillators.size(); i++)
        {
            Ref<CppWavetableOscillator> hop = Ref<CppWavetableOscillator>(Object::cast_to<CppWavetableOscillator>(oscillators[i]));
            hop->update(_frequency);
        }
}

void CppWavetableSynth::render(Ref<AudioStreamGeneratorPlayback> playback){
    // This needs thinking about differently to make sure it's always volume safe
    for (size_t i = 0; i < oscillators.size(); i++)
    {
        Ref<CppWavetableOscillator> hop = Ref<CppWavetableOscillator>(Object::cast_to<CppWavetableOscillator>(oscillators[i]));
            
        if (hop->currentlyPlaying())
        {
            PackedVector2Array buffer;
            for (int i = 0; i < playback->get_frames_available(); ++i)
            {
                float sample = hop->getSample();
                // For now sending nothing until we handle multiple voices
                buffer.push_back(Vector2(0.0f, 0.0f));
            }
            playback->push_buffer(buffer);
        }
       }
}

