#include "LFO.h"

void LFO::_bind_methods(){
    godot::ClassDB::bind_method(D_METHOD("getSample"), &LFO::getSample);
    godot::ClassDB::bind_method(D_METHOD("start"), &LFO::start);
    godot::ClassDB::bind_method(D_METHOD("update", "_frequency"), &LFO::update);
    godot::ClassDB::bind_method(D_METHOD("currentlyPlaying"), &LFO::currentlyPlaying);
    godot::ClassDB::bind_method(D_METHOD("stop"), &LFO::stop);
    godot::ClassDB::bind_method(D_METHOD("interpolateLiniarly"), &LFO::interpolateLiniarly);

    godot::ClassDB::bind_method(D_METHOD("getFrequency"), &LFO::getFrequency);
    godot::ClassDB::bind_method(D_METHOD("setFrequency", "_frequency"), &LFO::setFrequency);

    godot::ClassDB::bind_method(D_METHOD("getIncrement"), &LFO::getIncrement);
    godot::ClassDB::bind_method(D_METHOD("setIncrement", "_frequency"), &LFO::setIncrement);
    godot::ClassDB::bind_method(D_METHOD("_init", "_waveTable", "_sampleRate","_frequency"), &LFO::_init);
   
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "frequency"),"setFrequency", "getFrequency");

}

LFO::LFO()
{

};




float LFO::getSample(){
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

void LFO::_init(Array _waveTable, float _sampleRate, float _frequency){
    waveTable = _waveTable;
    //print_line(waveTable);
    sampleRate = _sampleRate;
    frequency = _frequency;
    isPlaying = false;
   
    
}

void LFO::setFrequency(float _frequency){
   
    frequency = _frequency;
    print_line("New LFO freq: ",_frequency);
    //frequency = _frequency;
    setIncrement(frequency);
}

float LFO::getFrequency() const{
    return frequency;
}

void LFO::setIncrement(float _frequency){
    increment = _frequency * ((float)waveTable.size() /sampleRate);
    //print_line("Increment: ", increment, " Index: ", index);
}

float LFO::getIncrement() const {
    return increment;
}

void LFO::start(){
    setFrequency(frequency);
    isPlaying = true;
    //print_line("Playing with freq ", frequency);
}





void LFO::update(float _frequency){
    setFrequency(_frequency);  
}

bool LFO::currentlyPlaying(){
    return isPlaying;
}


void LFO::stop(){
    isPlaying = false;
	index = 0.0f;
	increment = 0.0f;
}

float LFO::interpolateLiniarly(){
    int truncatedIndex = floor(index);
    //int nextIndex = ceil((int)index % waveTable.size());
    int nextIndex = (int)ceil(index) % waveTable.size();
    float nextIndexWeight = index - (float)truncatedIndex;
    if(index<0){
    //print_line("Index: ", index, " truncated index: ", truncatedIndex, " next index: ", nextIndex , " next index weight: ", nextIndexWeight);
    }

    float nextWave = waveTable[nextIndex];
    float trucWave = waveTable[truncatedIndex];
    return nextWave * nextIndexWeight + (1 - nextIndexWeight) * trucWave;
}
