#pragma once

#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/audio_stream_generator_playback.hpp"


using namespace godot;

class AudioStreamDoot: public RefCounted {
    GDCLASS(AudioStreamDoot, RefCounted)

    protected:
        static void _bind_methods();

    public:

};