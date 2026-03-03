#pragma once

#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/audio_stream_player3d.hpp"

using namespace godot;

class AudioNodeTest : public AudioStreamPlayer3D {
    GDCLASS(AudioNodeTest, AudioStreamPlayer3D)

   
    protected:
	static void _bind_methods();

    private:
        double timePassed = 0.0;
        const String NodeTestName = "Test Node";
        String changeMe = "Change Me"; 

    public:
        AudioNodeTest();
        ~AudioNodeTest();    
        String getTestName() const;
        void setChangeMe(String p_string);
        String getChangeMe() const ;
        void incrementSeconds();
        double getSecondsElapsed() const;
     



};