#include "CppWavetableOscillator.h"

void CppWavetableOscillator::_bind_methods(){
    godot::ClassDB::bind_method(D_METHOD("getSample"), &CppWavetableOscillator::getSample);
    godot::ClassDB::bind_method(D_METHOD("_init", "_waveTable", "_sampleRate","_frequency", "_detuneMult"), &CppWavetableOscillator::_init);
    godot::ClassDB::bind_method(D_METHOD("start"), &CppWavetableOscillator::start);
    godot::ClassDB::bind_method(D_METHOD("update", "_frequency"), &CppWavetableOscillator::update);
    godot::ClassDB::bind_method(D_METHOD("currentlyPlaying"), &CppWavetableOscillator::currentlyPlaying);
    godot::ClassDB::bind_method(D_METHOD("stop"), &CppWavetableOscillator::stop);
    godot::ClassDB::bind_method(D_METHOD("interpolateLiniarly"), &CppWavetableOscillator::interpolateLiniarly);

    godot::ClassDB::bind_method(D_METHOD("getFrequency"), &CppWavetableOscillator::getFrequency);
    godot::ClassDB::bind_method(D_METHOD("setFrequency", "_frequency"), &CppWavetableOscillator::setFrequency);
    godot::ClassDB::bind_method(D_METHOD("setDetune", "oscNum","oscCount","detuneAmount"), &CppWavetableOscillator::setDetune);

    godot::ClassDB::bind_method(D_METHOD("getIncrement"), &CppWavetableOscillator::getIncrement);
    godot::ClassDB::bind_method(D_METHOD("setIncrement", "_frequency"), &CppWavetableOscillator::setIncrement);
   
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "frequency"),"setFrequency", "getFrequency");

}

CppWavetableOscillator::CppWavetableOscillator()
{

};




float CppWavetableOscillator::getSample(){
    if (isPlaying == true){
        float prevIndex = index;
        index = godot::Math::fmod(index, (float)waveTable.size());
       
        
        
        float sample = interpolateLiniarly();
        index += increment;
        return sample;
    }
    else{
        return 0.0f;
    }
}

void CppWavetableOscillator::_init(Array _waveTable, float _sampleRate, float _frequency, float _detuneMult){
    waveTable = _waveTable;
    //print_line(waveTable);
    sampleRate = _sampleRate;
    frequency = _frequency;
    isPlaying = false;
    detuneMultiplyer = _detuneMult;
}

void CppWavetableOscillator::setFrequency(float _frequency){
    float newFrequency = _frequency * detune;
    frequency = newFrequency;
    //print_line("New freq: ",newFrequency);
    //frequency = _frequency;
    setIncrement(frequency);
}

float CppWavetableOscillator::getFrequency() const{
    return frequency;
}

void CppWavetableOscillator::setIncrement(float _frequency){
    increment = _frequency * ((float)waveTable.size() /sampleRate);
    print_line("Increment: ", increment, " Index: ", index);
}

float CppWavetableOscillator::getIncrement() const {
    return increment;
}

void CppWavetableOscillator::start(){
    setFrequency(frequency);
    isPlaying = true;
    //print_line("Playing with freq ", frequency);
}

void CppWavetableOscillator::setDetune(int oscNum, int oscCount, float detuneAmount){
    float middle=0.0f;
    float factor=0.0f;
    float oscnumplus1 = oscNum+1;
    if(oscCount % 2 == 0){
        middle = oscCount/2 + 0.5f;
        //print_line("even middle: ", middle);
    }
    else{
        middle = ceilf((float)oscCount/2);
        //print_line("odd middle: ", middle);

    }
    factor = oscnumplus1 - middle;
    detune = fabs(1 + factor * detuneAmount);
    print_line("Osc: " , oscNum , " middle: ",middle, " factor: ", factor, " detune amount: ", detuneAmount, " detune: " , detune);
    // if odd:
    // middle = ceil(oscCount/2)
    // else middle = oscCount/2 + 0.5
    // realoscnum = oscnum + 1
    // factor = realoscnum - middle
    // detune = detuneAmount * factor
    
}



void CppWavetableOscillator::update(float _frequency){
    setFrequency(_frequency);  
}

bool CppWavetableOscillator::currentlyPlaying(){
    return isPlaying;
}


void CppWavetableOscillator::stop(){
    isPlaying = false;
	index = 0.0f;
	increment = 0.0f;
}

float CppWavetableOscillator::interpolateLiniarly(){
    int truncatedIndex = floor(index);
    //int nextIndex = ceil((int)index % waveTable.size());
    int nextIndex = (int)ceil(index) % waveTable.size();
    float nextIndexWeight = index - (float)truncatedIndex;
    if(index<0){
    print_line("Index: ", index, " truncated index: ", truncatedIndex, " next index: ", nextIndex , " next index weight: ", nextIndexWeight);
    }

    float nextWave = waveTable[nextIndex];
    float trucWave = waveTable[truncatedIndex];
    return nextWave * nextIndexWeight + (1 - nextIndexWeight) * trucWave;
}
