
#include "CppWavetableSynth.h"
#include "godot_cpp/core/math.hpp"
#include "godot_cpp/classes/audio_stream_generator_playback.hpp"





 void CppWavetableSynth::_bind_methods(){
    godot::ClassDB::bind_method(D_METHOD("handleInput", "message"), &CppWavetableSynth::handleInput);
    godot::ClassDB::bind_method(D_METHOD("updateFrequency", "_frequency"), &CppWavetableSynth::updateFrequency);
    godot::ClassDB::bind_method(D_METHOD("updateDetune", "_detuneAmount"), &CppWavetableSynth::updateDetune);
    godot::ClassDB::bind_method(D_METHOD("updateAmplitude", "_amplitude"), &CppWavetableSynth::updateAmplitude);

    godot::ClassDB::bind_method(D_METHOD("render", "playback"), &CppWavetableSynth::render);


    godot::ClassDB::bind_method(D_METHOD("initOscillators", "_sampleRate", "_startingFreq", "type","numOscillators", "_detuneMult"), &CppWavetableSynth::initOscillators);




 }


CppWavetableSynth::CppWavetableSynth(){
    adsr = ADSR();
    adsr.setAttackRate(44100.0 * 0.5);
    adsr.setReleaseRate(44100.0);
};





void CppWavetableSynth::initOscillators(float _sampleRate, float _startingFreq, int type, int numOscillators, float _detuneMult) {
    Array waveTable;
    for(int i = 0; i < WAVETABLE_LENGTH; ++i){
    float value;
        switch (type)
        {
            //SAWTOOTHWAVE
        case 0:
            value = 2.0f * ((float)i / WAVETABLE_LENGTH) - 1.0f;
            break;
            //SQUAREWAVE
        case 1:
            value = sinf(Math_TAU * ((float)i / WAVETABLE_LENGTH)) >= 0.0 ? 1.0:-1.0;
            break;
            //SINEWAVE
        case 2:
            value = sinf(Math_TAU * ((float)i / WAVETABLE_LENGTH));
            break;
            //TRIANGLEWAVE
        case 3:
            value = 1 - fabs(((float)i / WAVETABLE_LENGTH)-0.5f) * 4;
            break;

        default:
            value = 0.0f;
            break;
        }

    waveTable.append(value);
    }
    
    for (size_t i = 0; i < numOscillators; i++)
    {
        
        Ref<CppWavetableOscillator> thosk;
        thosk.instantiate();
        thosk->_init(waveTable, _sampleRate, _startingFreq, _detuneMult);
        thosk->setDetune(i, numOscillators,_detuneMult);
       // print_line("Oscillator instantiated with id: ",thosk->get_instance_id());
        oscillators.push_back(thosk);

    }


       amplitude = 0.5f;
       centerFreq = _startingFreq;


}




void CppWavetableSynth::handleInput(bool message){
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
    //print_line("update freq: %s", _frequency);
    for (size_t i = 0; i < oscillators.size(); i++)
        {
            Ref<CppWavetableOscillator> hop = Ref<CppWavetableOscillator>(Object::cast_to<CppWavetableOscillator>(oscillators[i]));
            centerFreq = _frequency;
            hop->update(centerFreq);
        }
}

void CppWavetableSynth::updateDetune(float _detuneAmount) {
    //print_line("update detune: %s", _detuneAmount);
    for (size_t i = 0; i < oscillators.size(); i++)
        {
            Ref<CppWavetableOscillator> hop = Ref<CppWavetableOscillator>(Object::cast_to<CppWavetableOscillator>(oscillators[i]));
            hop->setDetune(i, oscillators.size(),_detuneAmount);
            
            hop->update(centerFreq);
        }
}

void CppWavetableSynth::updateAmplitude(float _amplitude) {
    amplitude = _amplitude;
}

void CppWavetableSynth::render(Ref<AudioStreamGeneratorPlayback> playback){
    // This needs thinking about differently to make sure it's always volume safe
    
    PackedVector2Array buffer;
    
    for (int i = 0; i < playback->get_frames_available(); ++i)
    {
        float sample = 0;
        for (size_t i = 0; i < oscillators.size(); i++)
        {
        Ref<CppWavetableOscillator> hop = Ref<CppWavetableOscillator>(Object::cast_to<CppWavetableOscillator>(oscillators[i]));
        
            if (hop->currentlyPlaying())
            {
                sample += hop->getSample() * amplitude;   
            }
        }

        buffer.push_back(Vector2(sample, sample));
    }
    playback->push_buffer(buffer);
}

