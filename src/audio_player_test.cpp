#include "audio_player_test.h"


void AudioNodeTest::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("setChangeMe", "p_string"), &AudioNodeTest::setChangeMe);
    ClassDB::bind_method(D_METHOD("getChangeMe"), &AudioNodeTest::getChangeMe);
    ClassDB::bind_method(D_METHOD("incrementSeconds"), &AudioNodeTest::incrementSeconds);
    ClassDB::bind_method(D_METHOD("getSecondsElapsed"), &AudioNodeTest::getSecondsElapsed);
    ClassDB::bind_method(D_METHOD("getTestName"), &AudioNodeTest::getTestName);
    ClassDB::bind_method(D_METHOD("printsPlayback", "refaudio"), &AudioNodeTest::printsPlayback);
   
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "changeMe"), "setChangeMe","getChangeMe");

}

AudioNodeTest::AudioNodeTest()
{
    timePassed = 0.0;
    
    changeMe = "Change Me"; 
}


AudioNodeTest::~AudioNodeTest()
{

}

void AudioNodeTest::setChangeMe(String p_string)
{
    changeMe = p_string;
    print_line("set change me called");
}


String AudioNodeTest::getTestName() const
{
    return NodeTestName;
}



String AudioNodeTest::getChangeMe() const 
{
    return changeMe;
    print_line("get change me called");

}


void AudioNodeTest::incrementSeconds()
{
    timePassed += 1.0;
}


double AudioNodeTest::getSecondsElapsed() const
{
    return timePassed;
}

void AudioNodeTest::printsPlayback(Ref<AudioStreamGeneratorPlayback> p){
    
    print_line("Audio gen %s", p);
}





